/**
 * Copyright 1998-2011 Epic Games, Inc. All Rights Reserved.
 */

#include "PS3NetworkPlatform.h" 

#include <netex/libnetctl.h>
#include <np/lookup.h>

/** PS3 specific session information for connecting */
struct FSessionInfoPS3 :
	public FSessionInfo
{
	/** The NP ID of the endpoint */
	SceNpId NpId;

	/** Zeros data */
	FSessionInfoPS3()
	{
		appMemzero(&NpId,sizeof(SceNpId));
	}
};

/** Holds the information needed for NAT traversal with an endpoint */
struct FNatTraversalEndpoint
{
	/** The NP ID of the endpoint */
	SceNpId NpId;
	/** The network information of the endpoint */
	FInternetIpAddr Addr;
	/** The connection id (cookie) for this endpoint */
	UINT ConnectionId;
	/** The status of the current connection (pending, active, etc.) */
	INT ConnectionStatus;
};

/** Holds the data for a NP signaling event so that it can be moved from one thread to another */
struct FNpSignalingEvent
{
	 /** The context id of the event */
	 DWORD ContextId;
	 /** The subject of the event */
	 DWORD SubjectId;
	 /** The event that is being processed */
	 INT Event;
	 /** Whether the event also contains an error code */
	 INT ErrorCode;
};

/** Holds the data for a NP manager event so that it can be moved from one thread to another */
struct FNpManagerEvent
{
	 /** The event that is being processed */
	 INT Event;
	 /** The result code associated with the event */
	 INT Result;
};

/** Holds the data used by NP */
struct FNpData
{
	/** Tracks whether GameSpy needs to synchronize the sign ins */
	UBOOL bNeedsGameSpyAuth;
	/** Whether or not manager/lookup has been initialized */
	UBOOL bNpManagerIsInitialized;
	/** The old connection status of the current user */
	INT LastConnectionStatus;
	/** The connection status of the current user */
	INT ConnectionStatus;
	/** The online id of the currently connected user */
	SceNpOnlineId OnlineId;
	/** The np id of the currently connected user */
	SceNpId NpId;
	/** The online name of the currently connected user */
	SceNpOnlineName OnlineName;
	/** Buffer holding the PSN ticket used by GameSpy for remote authentication */
	BYTE RemoteAuthTicket[SCE_NP_TICKET_MAX_SIZE];
	/** The size of the ticket that was returned to us */
	INT RemoteAuthTicketLength;
	/** Whether NP has gone offline or not */
	UBOOL bHasGoneOffline;
	/** Whether NAT info has been resolved or not */
	UBOOL bHasNatInfo;
	/** The NAT info for this PS3 */
	CellNetCtlNatInfo NatInfo;
	/** The context id returned by the signaling api */
	UINT ContextId;
	/** The network information for connecting */
	SceNpSignalingNetInfo NetInfo;
	/** The context allocated by calling create context */
	INT TitleContext;
	/** The context allocated by calling create transaction context */
	INT TransContext;
	/** Critical section because the rendering thread is what causes network callbacks */
	FCriticalSection NpSignalingSync;
	/** The set of NP signaling events that were caught on the rendering thread and need processing on the game thread */
	TArray<FNpSignalingEvent> SignalingEvents;
	/** Critical section because the rendering thread is what causes network callbacks */
	FCriticalSection NpManagerSync;
	/** The set of NP signaling events that were caught on the rendering thread and need processing on the game thread */
	TArray<FNpManagerEvent> ManagerEvents;
	/** Holds the list of NAT negotiated end points */
	TArray<FNatTraversalEndpoint> NatEndpoints;

	/** Default ctor that zeros the data members */
	inline FNpData(void)
	{
		bNpManagerIsInitialized = FALSE;
		appMemzero(this,(BYTE*)&NpSignalingSync - (BYTE*)this);
		LastConnectionStatus = ConnectionStatus = SCE_NP_MANAGER_STATUS_OFFLINE;
		NatInfo.size = sizeof(CellNetCtlNatInfo);
	}

	/** Initializes the NP lib */
	void InitNp(void)
	{
		// Do not re-init if there is a network connection out there
		if (GWorld == NULL || (GWorld && GWorld->GetNetDriver() == NULL))
		{
			// Init manager/lookup 
			if (!bNpManagerIsInitialized)
			{
				// Used to get connection state notifications
				INT Result = sceNpManagerRegisterCallback(_NpManagerCallback,this);
				if (Result == 0)
				{
					// Initialize the lookup service
					Result = sceNpLookupInit();
					if (Result == 0 || Result == SCE_NP_COMMUNITY_ERROR_ALREADY_INITIALIZED)
					{
						bNpManagerIsInitialized = TRUE;
						debugf(NAME_DevOnline,TEXT("NP, callback and lookup have been initialized"));
					}
					else
					{
						debugf(NAME_DevOnline,TEXT("Failed to init NP Lookup with error code 0x%08X"),Result);
					}
				}
				else
				{
					debugf(NAME_DevOnline,TEXT("Failed to set NP connection callback with error code 0x%08X"),Result);
				}
			}
		}
		else
		{
			// Close any net connection in this case
			if (GWorld && GWorld->GetNetDriver())
			{
				GEngine->SetProgress(PMT_ConnectionFailure,LocalizeError(TEXT("ConnectionFailed_Title"), TEXT("Engine")), LocalizeError(TEXT("ConnectionFailed"), TEXT("Engine")));
			}
		}
	}

	/**
	 * Cleans up the NP state so it can be restarted
	 */
	void CleanupNp(void)
	{
		// We are terminating, so treat as offline
		LastConnectionStatus = ConnectionStatus = SCE_NP_MANAGER_STATUS_OFFLINE;
		// Stop all nat negotiated connections
		RemoveAllNatConnections();
		// Stop the signaling context
		sceNpSignalingDestroyCtx(ContextId);
		debugf(NAME_DevOnline,TEXT("NP has gone offline"));

		// Mark NP manager as stopped, it will be restarted next tick
		bNpManagerIsInitialized = FALSE;

		bHasGoneOffline = TRUE;
	}

	/**
	 * Callback handler for connection status changes
	 *
	 * @param Event the event that is being triggered
	 * @param Result the status code of the event
	 * @param This pointer to the FNpData object to forward the call to
	 */
	static void _NpManagerCallback(INT Event,INT Result, void* This)
	{
		check(This != NULL);
		((FNpData*)This)->NpManagerCallback(Event,Result);
	}

	/**
	 * Callback handler for connection status changes on a specific instance
	 *
	 * @param InEvent the event that is being triggered
	 * @param InResult the status code of the event
	 */
	void NpManagerCallback(INT InEvent,INT InResult)
	{
		FScopeLock sl(&NpManagerSync);
		// Add to the queue so that the game thread can process next tick
		INT AddIndex = ManagerEvents.AddZeroed();
		FNpManagerEvent& EventEntry = ManagerEvents(AddIndex);
		EventEntry.Event = InEvent;
		EventEntry.Result = InResult;
	}

	/**
	 * Processes any queued NP manager events
	 */
	void TickNpManagerEvents(void)
	{
		FScopeLock sl(&NpManagerSync);
		// Now that the rendering thread can't add, iterate over the events and process
		for (INT Index = 0; Index < ManagerEvents.Num() && bNpManagerIsInitialized; Index++)
		{
			const FNpManagerEvent& EventEntry = ManagerEvents(Index);
			debugf(NAME_DevOnline,
				TEXT("NP Manager event: Event = %d, Result = %d"),
				EventEntry.Event,
				EventEntry.Result);
			// Don't process errors
			if (EventEntry.Event > -1)
			{
				if (EventEntry.Event == SCE_NP_MANAGER_EVENT_GOT_TICKET)
				{
					if (EventEntry.Result > 0)
					{
						bNeedsGameSpyAuth = TRUE;
						// The size is in the result if the result is positive otherwise it's an error
						RemoteAuthTicketLength = EventEntry.Result;
						size_t Size = sizeof(RemoteAuthTicket);
						sceNpManagerGetTicket(RemoteAuthTicket,&Size);
					}
					else
					{
						debugf(NAME_DevOnline,
							TEXT("Failed to get ticket for remote authentication with 0x%08X"),
							EventEntry.Result);
						// Tear down NP and try again
						CleanupNp();
					}
				}
			}
			else
			{
				// NP is broken, restart it
				CleanupNp();
			}
		}
		// Clean out any events since we've processed them all
		ManagerEvents.Empty();
	}

	/**
	 * Callback handler for the np signaling api
	 *
	 * @param ContxtId the context id
	 * @param SubjectId the subject id
	 * @param Event the event type that has occured
	 * @param ErrorCode the error code associated with the event
	 * @param This pointer to the FNpData object to forward the call to
	 */
	static void _NpSignalingHandler(UINT ContxtId,UINT SubjectId,INT Event,INT ErrorCode,void* This)
	{
		check(This != NULL);
		((FNpData*)This)->NpSignalingHandler(ContxtId,SubjectId,Event,ErrorCode);
	}

	/**
	 * Callback handler for the np signaling api
	 *
	 * @param InContextId the context id
	 * @param InSubjectId the subject id
	 * @param InEvent the event type that has occured
	 * @param InErrorCode the error code associated with the event
	 */
	void NpSignalingHandler(DWORD InContextId,DWORD InSubjectId,INT InEvent,INT InErrorCode)
	{
		FScopeLock sl(&NpSignalingSync);
		// Add to the queue so that the game thread can process next tick
		INT AddIndex = SignalingEvents.AddZeroed();
		FNpSignalingEvent& EventEntry = SignalingEvents(AddIndex);
		EventEntry.ContextId = InContextId;
		EventEntry.SubjectId = InSubjectId;
		EventEntry.Event = InEvent;
		EventEntry.ErrorCode = InErrorCode;
	}

	/**
	 * Services the queued np signaling events on the game thread
	 */
	void TickNpSignalingEvents(void)
	{
		FScopeLock sl(&NpSignalingSync);
		// Now that the rendering thread can't add, iterate over the events and process
		for (INT Index = 0; Index < SignalingEvents.Num() && bNpManagerIsInitialized; Index++)
		{
			const FNpSignalingEvent& EventEntry = SignalingEvents(Index);
			debugf(NAME_DevOnline,
				TEXT("NP Signaling event: ContextId = %d, SubjectId = %d, Event = %d, ErrorCode = %d"),
				EventEntry.ContextId,
				EventEntry.SubjectId,
				EventEntry.Event,
				EventEntry.ErrorCode);
			// Figure out what event happened
			switch (EventEntry.Event)
			{
				case SCE_NP_SIGNALING_EVENT_EXT_ACTIVATED:
				{
					// Create a new entry for this
					AddNatConnection(EventEntry.SubjectId);
					break;
				}
				case SCE_NP_SIGNALING_EVENT_DEAD:
				{
					// Remove the connection from the list
					RemoveNatConnection(EventEntry.SubjectId);
					break;
				}
				case SCE_NP_SIGNALING_EVENT_ESTABLISHED:
				{
					// Update the connection to activated
					UpdateNatConnection(EventEntry.SubjectId);
					break;
				}
			}
			// Check to see if NP went down
			if (EventEntry.ErrorCode == SCE_NP_ERROR_OFFLINE)
			{
				// Clean up so that it can be restarted next tick
				CleanupNp();
			}
		}
		// Clean out any events since we've processed them all
		SignalingEvents.Empty();
	}

	/**
	 * Sets up the nat information needed for nat traversal
	 */
	inline void TickNatTasks(void)
	{
		// Query the nat info
		if (bHasNatInfo == FALSE)
		{
			// Ask for the current nat info
			INT Result = cellNetCtlGetNatInfo(&NatInfo);
			if (Result == 0)
			{
				// Make sure that STUN negotiation has completed
				if (NatInfo.stun_status != CELL_NET_CTL_NATINFO_STUN_UNCHECKED)
				{
					NetInfo.size = sizeof(SceNpSignalingNetInfo);
					// Request our external network address
					if (sceNpSignalingGetLocalNetInfo(ContextId,&NetInfo) == 0)
					{
						debugf(NAME_DevOnline,
							TEXT("NAT resolved. Type = %d, STUN status = %d, UPnP status = %d"),
							NatInfo.nat_type,
							NatInfo.stun_status,
							NatInfo.upnp_status);
						debugf(NAME_DevOnline,
							TEXT("Net info: Internal IP = %s, External IP = %s, NP Port = %d, NP Port Status = %d"),
							ANSI_TO_TCHAR(inet_ntoa(NetInfo.local_addr)),
							ANSI_TO_TCHAR(inet_ntoa(NetInfo.mapped_addr)),
							NetInfo.npport,
							NetInfo.npport_status);
						bHasNatInfo = TRUE;
					}
				}
			}
		}
	}

	/**
	 * Checks the current status to determine changes in sign in and/or connection
	 */
	void Tick(FLOAT DeltaTime)
	{
		// Tick any queued events from the rendering thread
		TickNpManagerEvents();
		TickNpSignalingEvents();
		// Only tick these if NP didn't go offline in the signaling events
		if (bNpManagerIsInitialized)
		{
			// Tick the nat task
			TickNatTasks();
			// See if the sign in has completed
			if (sceNpManagerGetStatus(&ConnectionStatus) == 0)
			{
				if (ConnectionStatus == SCE_NP_MANAGER_STATUS_ONLINE &&
					LastConnectionStatus != SCE_NP_MANAGER_STATUS_ONLINE)
				{
					// Grab various sign in state
					sceNpManagerGetOnlineId(&OnlineId);
					sceNpManagerGetOnlineName(&OnlineName);
					sceNpManagerGetNpId(&NpId);
					// Kick off ticket read
					sceNpManagerRequestTicket(&NpId,PS3_SERVICE_ID,NULL,0,NULL,0);
					debugf(NAME_DevOnline,
						TEXT("NP login status has changed. Requesting ticket for %s"),
						UTF8_TO_TCHAR(OnlineName.data));
					// Start the signaling task
					if (sceNpSignalingCreateCtx(&NpId,NULL,NULL,&ContextId) == 0)
					{
						// Register that we want extended information
						sceNpSignalingAddExtendedHandler(ContextId,_NpSignalingHandler,this);
					}
					bHasGoneOffline = FALSE;
				}
				LastConnectionStatus = ConnectionStatus;
			}
		}
		else
		{
			// NP went down, so re-init
			InitNp();
		}
	}

	/**
	 * @return whether NP has gone offline or not
	 */
	inline UBOOL HasGoneOffline(void)
	{
		return bHasGoneOffline;
	}

	/** Resets the offline event flag */
	inline void ResetOfflineEvent(void)
	{
		bHasGoneOffline = FALSE;
	}

	/** @return TRUE if the user can chat with online players, FALSE otherwise */
	inline UBOOL CanCommunicate(void)
	{
		INT IsRestricted = 0;
		INT ReturnCode = sceNpManagerGetChatRestrictionFlag(&IsRestricted);
		debugf(NAME_DevOnline,TEXT("sceNpManagerGetChatRestrictionFlag() returned 0x%08X"),ReturnCode);
		if (ReturnCode == CELL_OK)
		{
			return IsRestricted == 0 ? TRUE : FALSE;
		}
		return TRUE;
	}

	/** @return TRUE if the user can play online, FALSE otherwise */
	inline UBOOL CanPlayOnline(void)
	{
		INT IsRestricted = 0;
		INT Age = 0;
		INT ReturnCode = sceNpManagerGetContentRatingFlag(&IsRestricted,&Age);
		debugf(NAME_DevOnline,TEXT("sceNpManagerGetContentRatingFlag() returned 0x%08X"),ReturnCode);
		if (ReturnCode == CELL_OK)
		{
			return IsRestricted == 0 || Age >= 18 ? TRUE : FALSE;
		}
		return TRUE;
	}

	/** @return The nat configuration for this PS3 */
	inline ENATType GetNatType(void)
	{
		// If we've queried the nat info, then return the info
		if (bHasNatInfo)
		{
			// Map their type to ours
			switch (NatInfo.nat_type)
			{
				case 1:
				{
					return NAT_Open;
				}
				case 2:
				{
					return NAT_Moderate;
				}
				case 3:
				{
					return NAT_Strict;
				}
			}
		}
		return NAT_Strict;
	}

	/**
	 * Searches the NAT endpoint list for the NP ID
	 *
	 * @param NpId the NP ID we are searching for
	 *
	 * @return a pointer to the item or null if not found
	 */
	FNatTraversalEndpoint* FindNatEndpoint(SceNpId* NpId)
	{
		for (INT Index = 0; Index < NatEndpoints.Num(); Index++)
		{
			// If these NP IDs match, return the entry
			if (sceNpUtilCmpNpId(NpId,&NatEndpoints(Index).NpId) == 0)
			{
				return &NatEndpoints(Index);
			}
		}
		return NULL;
	}

	/**
	 * Searches the NAT endpoint list for the connection id
	 *
	 * @param ConnectionId the connection id we are searching for
	 *
	 * @return a pointer to the item or null if not found
	 */
	FNatTraversalEndpoint* FindNatEndpoint(INT ConnectionId)
	{
		for (INT Index = 0; Index < NatEndpoints.Num(); Index++)
		{
			// If these connection IDs match, return the entry
			if (ConnectionId == NatEndpoints(Index).ConnectionId)
			{
				return &NatEndpoints(Index);
			}
		}
		return NULL;
	}

	/**
	 * Starts the NP negotiation of a connection to an end point using
	 * the NP ID to find it
	 *
	 * @param NpIdToAdd the NP ID to start the handshaking with
	 *
	 * @return TRUE if the task started successfully, FALSE otherwise
	 */
	UBOOL AddNatConnection(SceNpId* NpIdToAdd)
	{
		INT Return = 0;
		if (FindNatEndpoint(NpIdToAdd) == NULL)
		{
			// Add a new entry
			INT AddIndex = NatEndpoints.AddZeroed();
			FNatTraversalEndpoint& NewNatEndpoint = NatEndpoints(AddIndex);
			// Copy the NP ID for later use
			appMemcpy(&NewNatEndpoint.NpId,NpIdToAdd,sizeof(SceNpId));
			// Set to pending
			NewNatEndpoint.ConnectionStatus = SCE_NP_SIGNALING_CONN_STATUS_PENDING;
			// Start the nat process
			Return = sceNpSignalingActivateConnection(ContextId,
				&NewNatEndpoint.NpId,
				&NewNatEndpoint.ConnectionId);
			debugf(NAME_DevOnline,
				TEXT("sceNpSignalingActivateConnection(%d,%s,) returned 0x%08X"),
				ContextId,
				ANSI_TO_TCHAR(NewNatEndpoint.NpId.handle.data),
				Return);
			if (Return != 0)
			{
				NatEndpoints.Remove(AddIndex);
			}
		}
		return Return == 0;
	}

	/**
	 * Adds a connection via the event information
	 *
	 * @param SubjectId the NP ID to start the handshaking with
	 *
	 * @return TRUE if the task started successfully, FALSE otherwise
	 */
	UBOOL AddNatConnection(DWORD SubjectId)
	{
		INT Return = 0;
		if (FindNatEndpoint(SubjectId) == NULL)
		{
			// Add a new entry
			INT AddIndex = NatEndpoints.AddZeroed();
			FNatTraversalEndpoint& NewNatEndpoint = NatEndpoints(AddIndex);
			// Copy the connection id for matching up later
			NewNatEndpoint.ConnectionId = SubjectId;
			SceNpSignalingConnectionInfo Info;
			appMemzero(&Info,sizeof(SceNpSignalingConnectionInfo));
			// Get their NP ID, so we can track who they are
			INT Return = sceNpSignalingGetConnectionInfo(ContextId,
				SubjectId,
				SCE_NP_SIGNALING_CONN_INFO_PEER_NPID,
				&Info);
			debugf(NAME_DevOnline,
				TEXT("sceNpSignalingGetConnectionInfo(,,SCE_NP_SIGNALING_CONN_INFO_PEER_NPID,) returned 0x%08X"),
				Return);
			if (Return == 0)
			{
				debugf(NAME_DevOnline,
					TEXT("Connection activated for %s"),
					UTF8_TO_TCHAR(Info.npId.handle.data));
				// Store their NP ID
				appMemcpy(&NewNatEndpoint.NpId,&Info.npId,sizeof(SceNpId));
				appMemzero(&Info,sizeof(SceNpSignalingConnectionInfo));
				// Now read the connection data for this
				Return = sceNpSignalingGetConnectionInfo(ContextId,
					SubjectId,
					SCE_NP_SIGNALING_CONN_INFO_PEER_ADDRESS,
					&Info);
				debugf(NAME_DevOnline,
					TEXT("sceNpSignalingGetConnectionInfo(,,SCE_NP_SIGNALING_CONN_INFO_PEER_ADDRESS,) returned 0x%08X"),
					Return);
				if (Return == 0)
				{
					// Copy the address information
					NewNatEndpoint.Addr.SetIp(Info.address.addr);
					NewNatEndpoint.Addr.SetPort(ntohl(Info.address.port));
					debugf(NAME_DevOnline,
						TEXT("Remote address is: %s"),
						*NewNatEndpoint.Addr.ToString(TRUE));
					// Set to pending
					NewNatEndpoint.ConnectionStatus = SCE_NP_SIGNALING_CONN_STATUS_PENDING;
					// Register the remote caller too
					Return = sceNpSignalingActivateConnection(ContextId,
						&NewNatEndpoint.NpId,
						&NewNatEndpoint.ConnectionId);
					debugf(NAME_DevOnline,
						TEXT("sceNpSignalingActivateConnection(%d,%s,) returned 0x%08X"),
						ContextId,
						ANSI_TO_TCHAR(NewNatEndpoint.NpId.handle.data),
						Return);
				}
			}
			if (Return != 0)
			{
				NatEndpoints.Remove(AddIndex);
			}
		}
		return Return == 0;
	}

	/**
	 * Updates the connection status for the matching connection
	 *
	 * @param ConnectionId the connection id to stop NAT communication with
	 */
	void UpdateNatConnection(DWORD ConnectionId)
	{
		// Search the NAT endpoints for the player that is leaving
		for (INT Index = 0; Index < NatEndpoints.Num(); Index++)
		{
			// If these NP IDs match, deactivate the entry and remove it
			if (ConnectionId == NatEndpoints(Index).ConnectionId)
			{
				SceNpSignalingConnectionInfo Info;
				appMemzero(&Info,sizeof(SceNpSignalingConnectionInfo));
				// Now read the updated connection data for this
				INT Return = sceNpSignalingGetConnectionInfo(ContextId,
					ConnectionId,
					SCE_NP_SIGNALING_CONN_INFO_PEER_ADDRESS,
					&Info);
				debugf(NAME_DevOnline,
					TEXT("sceNpSignalingGetConnectionInfo(,,SCE_NP_SIGNALING_CONN_INFO_PEER_ADDRESS,) returned 0x%08X"),
					Return);
				NatEndpoints(Index).ConnectionStatus = SCE_NP_SIGNALING_CONN_STATUS_ACTIVE;
				// Copy the address information
				NatEndpoints(Index).Addr.SetIp(Info.address.addr);
				NatEndpoints(Index).Addr.SetPort(ntohl(Info.address.port));
				debugf(NAME_DevOnline,
					TEXT("Setting status for %s (%s) to active"),
					UTF8_TO_TCHAR(NatEndpoints(Index).NpId.handle.data),
					*NatEndpoints(Index).Addr.ToString(TRUE));
				return;
			}
		}
	}

	/**
	 * Determines if the endpoint is inactive or not
	 *
	 * @param NpId the NP ID of the endpoint
	 *
	 * @return TRUE if is inactive, FALSE otherwise
	 */
	UBOOL IsNatEndpointInactive(SceNpId* NpId)
	{
		FNatTraversalEndpoint* Endpoint = FindNatEndpoint(NpId);
		if (Endpoint)
		{
			return Endpoint->ConnectionStatus == SCE_NP_SIGNALING_CONN_STATUS_INACTIVE;
		}
		// Inactive is the default when not found
		return TRUE;
	}

	/**
	 * Determines if the endpoint is active or not
	 *
	 * @param NpId the NP ID of the endpoint
	 *
	 * @return TRUE if is active, FALSE otherwise
	 */
	UBOOL IsNatEndpointActive(SceNpId* NpId)
	{
		FNatTraversalEndpoint* Endpoint = FindNatEndpoint(NpId);
		if (Endpoint)
		{
			return Endpoint->ConnectionStatus == SCE_NP_SIGNALING_CONN_STATUS_ACTIVE;
		}
		return FALSE;
	}

	/**
	 * Determines if the endpoint is pending or not
	 *
	 * @param NpId the NP ID of the endpoint
	 *
	 * @return TRUE if is pending, FALSE otherwise
	 */
	UBOOL IsNatEndpointPending(SceNpId* NpId)
	{
		FNatTraversalEndpoint* Endpoint = FindNatEndpoint(NpId);
		if (Endpoint)
		{
			return Endpoint->ConnectionStatus == SCE_NP_SIGNALING_CONN_STATUS_PENDING;
		}
		return FALSE;
	}

	/**
	 * Removes the connection from the NAT negotiated list
	 *
	 * @param NpIdToRemove the NP ID to stop NAT communication with
	 */
	void RemoveNatConnection(SceNpId* NpIdToRemove)
	{
		// Search the NAT endpoints for the player that is leaving
		for (INT Index = 0; Index < NatEndpoints.Num(); Index++)
		{
			// If these NP IDs match, deactivate the entry and remove it
			if (sceNpUtilCmpNpId(NpIdToRemove,&NatEndpoints(Index).NpId) == 0)
			{
				debugf(NAME_DevOnline,
					TEXT("Removing %s from the NAT endpoints"),
					ANSI_TO_TCHAR(NatEndpoints(Index).NpId.handle.data));
				// Disconnect the nat endpoint
				INT Return = sceNpSignalingDeactivateConnection(ContextId,
					NatEndpoints(Index).ConnectionId);
				debugf(NAME_DevOnline,
					TEXT("sceNpSignalingDeactivateConnection(%d,%d) returned 0x%08X"),
					ContextId,
					NatEndpoints(Index).ConnectionId,
					Return);
				NatEndpoints.Remove(Index);
				return;
			}
		}
	}

	/**
	 * Removes the connection from the NAT negotiated list
	 *
	 * @param ConnectionId the connection id to stop NAT communication with
	 */
	void RemoveNatConnection(DWORD ConnectionId)
	{
		// Search the NAT endpoints for the player that is leaving
		for (INT Index = 0; Index < NatEndpoints.Num(); Index++)
		{
			// If these NP IDs match, deactivate the entry and remove it
			if (ConnectionId == NatEndpoints(Index).ConnectionId)
			{
				debugf(NAME_DevOnline,
					TEXT("Removing %s from the NAT endpoints"),
					UTF8_TO_TCHAR(NatEndpoints(Index).NpId.handle.data));
				// Disconnect the nat endpoint
				INT Return = sceNpSignalingDeactivateConnection(ContextId,
					NatEndpoints(Index).ConnectionId);
				debugf(NAME_DevOnline,
					TEXT("sceNpSignalingDeactivateConnection(%d,%d) returned 0x%08X"),
					ContextId,
					NatEndpoints(Index).ConnectionId,
					Return);
				NatEndpoints.Remove(Index);
				return;
			}
		}
	}

	/**
	 * Removes the connection from the NAT negotiated list
	 *
	 * @param NpIdToRemove the NP ID to stop NAT communication with
	 */
	void RemoveAllNatConnections(void)
	{
		// Search the NAT endpoints for the player that is leaving
		for (INT Index = 0; Index < NatEndpoints.Num(); Index++)
		{
			debugf(NAME_DevOnline,
				TEXT("Removing %s from the NAT endpoints"),
				ANSI_TO_TCHAR(NatEndpoints(Index).NpId.handle.data));
			// Disconnect the nat endpoint
			INT Return = sceNpSignalingTerminateConnection(ContextId,
				NatEndpoints(Index).ConnectionId);
			debugf(NAME_DevOnline,
				TEXT("sceNpSignalingTerminateConnection(%d,%d) returned 0x%08X"),
				ContextId,
				NatEndpoints(Index).ConnectionId,
				Return);
		}
		NatEndpoints.Empty();
	}
};
