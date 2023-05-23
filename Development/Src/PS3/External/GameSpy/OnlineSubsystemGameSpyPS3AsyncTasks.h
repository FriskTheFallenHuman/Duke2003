/**
 * Copyright 1998-2011 Epic Games, Inc. All Rights Reserved.
 */

/**
 * Used to poll for the NAT connection to be added
 */
class FOnlineAsyncTaskAddNatConnection :
	public FOnlineAsyncTaskGameSpy
{
	/** The NP ID to check the status of */
	SceNpId* NpId;
	/** The NP data object to query */
	FNpData* NpData;
	/** The session info to update with the destination address */
	FSessionInfoPS3* SessionInfo;

public:
	/**
	 * Initializes members and starts the process
	 */
	FOnlineAsyncTaskAddNatConnection(FNpData* InNpData,SceNpId* InNpId,FSessionInfoPS3* InSessionInfo,TArray<FScriptDelegate>* InScriptDelegates) :
		FOnlineAsyncTaskGameSpy(InScriptDelegates,TEXT("AddNatConnection")),
		NpId(InNpId),
		NpData(InNpData),
		SessionInfo(InSessionInfo)
	{
	}

	/**
	 * Ticks the NP nat connection task
	 *
	 * @param DeltaTime the amount of time since the last tick
	 */
	virtual void Tick(FLOAT DeltaTime)
	{
		if (NpData && NpId)
		{
			// If we are no longer pending, check the status
			if (NpData->IsNatEndpointPending(NpId) == FALSE)
			{
				if (NpData->IsNatEndpointActive(NpId))
				{
					// Get the endpoint so we can copy the finalized data
					FNatTraversalEndpoint* Endpoint = NpData->FindNatEndpoint(NpId);
					check(Endpoint);
					// Copy the finalized address information
					SessionInfo->HostAddr = Endpoint->Addr;
					CompletionStatus = S_OK;
				}
				else
				{
					CompletionStatus = E_FAIL;
				}
			}
		}
		else
		{
			CompletionStatus = E_FAIL;
		}
	}
};

/**
 * Formats the NP ID in a session info to string form
 *
 * @param SessionInfoPs3 the object to copy the NP ID data to
 */
static FString appNpIdToUrl(FSessionInfoPS3* SessInfoPs3)
{
	QWORD Np2 = (QWORD&)SessInfoPs3->NpId.opt;
	QWORD Np3 = (QWORD&)SessInfoPs3->NpId.reserved;
	// Format via printf
	return FString::Printf(TEXT("?Np1=%s?Np2=%lli?Np3=%lli"),
		UTF8_TO_TCHAR(SessInfoPs3->NpId.handle.data),
		Np2,
		Np3);
}

/**
 * Copies the NP ID from the URL to the session info
 *
 * @param SessionInfoPs3 the object to copy the NP ID data to
 * @param Url the FURL object to read the NP ID data from
 */
static void appCopyPs3SessionInfoFromUrl(FSessionInfoPS3* SessInfoPs3,const FURL& Url)
{
	QWORD Np2 = 0;
	QWORD Np3 = 0;
	// We need to parse the NP ID out of the data
	const TCHAR* Value = Url.GetOption(TEXT("Np2="),TEXT(""));
	if (Value != NULL)
	{
		Np2 = atoll(TCHAR_TO_ANSI(Value));
	}
	const TCHAR* Value2 = Url.GetOption(TEXT("Np3="),TEXT(""));
	if (Value2 != NULL)
	{
		Np3 = atoll(TCHAR_TO_ANSI(Value2));
	}
	// Now copy the data in
	SceNpId* HostNpId = &SessInfoPs3->NpId;
	appMemcpy(HostNpId->opt,&Np2,sizeof(QWORD));
	appMemcpy(HostNpId->reserved,&Np3,sizeof(QWORD));
	// Finally copy their player name in
	strcpy(HostNpId->handle.data,TCHAR_TO_UTF8(Url.GetOption(TEXT("Np1="),TEXT(""))));
}
