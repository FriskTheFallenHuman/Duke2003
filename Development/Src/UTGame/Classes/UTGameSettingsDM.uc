/**
 * Copyright 1998-2011 Epic Games, Inc. All Rights Reserved.
 */

/** Holds the settings that are advertised for a match */
class UTGameSettingsDM extends UTGameSettingsCommon;

defaultproperties
{
	// Set the specific game mode
	LocalizedSettings(0)=(Id=CONTEXT_GAME_MODE,ValueIndex=CONTEXT_GAME_MODE_DM,AdvertisementType=ODAT_OnlineService)

	//goal score 30 kills
	Properties(2)=(PropertyId=PROPERTY_GOALSCORE,Data=(Type=SDT_Int32,Value1=30),AdvertisementType=ODAT_OnlineService)
	
	//time limit 0
	Properties(3)=(PropertyId=PROPERTY_TIMELIMIT,Data=(Type=SDT_Int32,Value1=0),AdvertisementType=ODAT_OnlineService)
}
