/**
 * Copyright 1998-2011 Epic Games, Inc. All Rights Reserved.
 */
class UTVoice_Gus extends UTVoice
	abstract;

/** 
BeginSearchRoutine
PlasmaCleanerBurningMoreEfficient

Zap_Alt
TacticalAssessmentComplete
UndesirableLosses
*/

static function bool SendLocationUpdate(Controller Sender, PlayerReplicationInfo Recipient, Name Messagetype, UTGame G, Pawn StatusPawn, optional bool bDontSendMidfield)
{
	return false;
}

defaultproperties
{
	LocationSpeechOffset=3
	
	TauntSounds(0)=SoundNodeWave'A_VoicePack_GEARSofWAR_Gus.AmoCutYourHeadOff'
	TauntSounds(1)=SoundNodeWave'A_VoicePack_GEARSofWAR_Gus.AndDead'
	TauntSounds(2)=SoundNodeWave'A_VoicePack_GEARSofWAR_Gus.BackInYourHole'
	TauntSounds(3)=SoundNodeWave'A_VoicePack_GEARSofWAR_Gus.Booooom'
	TauntSounds(4)=SoundNodeWave'A_VoicePack_GEARSofWAR_Gus.Catch'
	TauntSounds(5)=SoundNodeWave'A_VoicePack_GEARSofWAR_Gus.DoubleDead'
    TauntSounds(6)=SoundNodeWave'A_VoicePack_GEARSofWAR_Gus.EatThatBitch'
	TauntSounds(7)=SoundNodeWave'A_VoicePack_GEARSofWAR_Gus.EatThatSucker'
	TauntSounds(8)=SoundNodeWave'A_VoicePack_GEARSofWAR_Gus.GetSomeBaby'
	TauntSounds(9)=SoundNodeWave'A_VoicePack_GEARSofWAR_Gus.GotIt_02'
	TauntSounds(10)=SoundNodeWave'A_VoicePack_GEARSofWAR_Gus.Hahaha'
	TauntSounds(11)=SoundNodeWave'A_VoicePack_GEARSofWAR_Gus.MyMomCanKiilYouWeakAss'
	
	AckSounds(0)=SoundNodeWave'A_Character_CorruptEnigma.Mean_BotStatus.A_BotStatus_Corrupt_Acknowledged'
	AckSounds(1)=SoundNodeWave'A_Character_CorruptEnigma.Mean_BotStatus.A_BotStatus_Corrupt_Affirmative'

	FriendlyFireSounds(0)=SoundNodeWave'A_Character_CorruptEnigma.Mean_BotStatus.A_BotStatus_Corrupt_IncorrectTarget'
	FriendlyFireSounds(1)=SoundNodeWave'A_Character_CorruptEnigma.Mean_BotStatus.A_BotStatus_Corrupt_SameTeam'

	NeedOurFlagSounds(0)=SoundNodeWave'A_Character_CorruptEnigma.Mean_BotStatus.A_BotStatus_Corrupt_FlagInPossession'

	GotYourBackSounds(0)=SoundNodeWave'A_Character_CorruptEnigma.Mean_BotStatus.A_BotStatus_Corrupt_IveGotYourBack'
	GotYourBackSounds(1)=SoundNodeWave'A_Character_CorruptEnigma.Mean_BotStatus.A_BotStatus_Corrupt_GotYourBack'
	GotYourBackSounds(2)=SoundNodeWave'A_Character_CorruptEnigma.Mean_BotStatus.A_BotStatus_Corrupt_CoveringYou'

	SniperSounds(0)=SoundNodeWave'A_Character_CorruptEnigma.Mean_BotStatus.A_BotStatus_Corrupt_SurpressTheSniper'

	InPositionSounds(0)=SoundNodeWave'A_Character_CorruptEnigma.Mean_BotStatus.A_BotStatus_Corrupt_UnitInPosition'

	IncomingSound=SoundNodeWave'A_Character_CorruptEnigma.Mean_BotStatus.A_BotStatus_Corrupt_Incoming'
	EnemyFlagCarrierSound=SoundNodeWave'A_Character_CorruptEnigma.Mean_BotStatus.A_BotStatus_Corrupt_EnemyFlagCarrier'
	MidFieldSound=SoundNodeWave'A_Character_CorruptEnigma.Mean_BotStatus.A_BotStatus_Corrupt_Midfield'

	EnemyFlagCarrierHereSound=SoundNodeWave'A_Character_CorruptEnigma.Mean_BotStatus.A_BotStatus_Corrupt_EnemyFlagCarrierHere'
	EnemyFlagCarrierHighSound=SoundNodeWave'A_Character_CorruptEnigma.Mean_BotStatus.A_BotStatus_Corrupt_EnemyFlagCarrierGoingHigh'
	EnemyFlagCarrierLowSound=SoundNodeWave'A_Character_CorruptEnigma.Mean_BotStatus.A_BotStatus_Corrupt_EnemyFlagCarrierGoingLow'

	HaveFlagSounds(0)=SoundNodeWave'A_Character_CorruptEnigma.Mean_BotStatus.A_BotStatus_Corrupt_FlagInPossession'

	AreaSecureSounds(0)=SoundNodeWave'A_Character_CorruptEnigma.Mean_BotStatus.A_BotStatus_Corrupt_AreaSecure'

	GotOurFlagSound=SoundNodeWave'A_Character_CorruptEnigma.Mean_BotStatus.A_BotStatus_Corrupt_FlagInPossession'
}