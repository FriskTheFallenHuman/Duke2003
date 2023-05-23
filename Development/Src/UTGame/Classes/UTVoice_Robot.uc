/**
 * Copyright 1998-2011 Epic Games, Inc. All Rights Reserved.
 */
class UTVoice_Robot extends UTVoice
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

	TauntSounds(0)=SoundNodeWave'A_VoicePack_GEARSofWAR_Marcus.JustDieWillYa_Loud01'
	TauntSounds(1)=SoundNodeWave'A_VoicePack_GEARSofWAR_Marcus.OhYeah_Loud01'
	TauntSounds(2)=SoundNodeWave'A_VoicePack_GEARSofWAR_Marcus.FuckYou_02'
	TauntSounds(3)=SoundNodeWave'A_VoicePack_GEARSofWAR_Marcus.Haha_Yeah02'
	TauntSounds(4)=SoundNodeWave'A_VoicePack_GEARSofWAR_Marcus.TakeIt_Loud03'
	TauntSounds(5)=SoundNodeWave'A_VoicePack_GEARSofWAR_Marcus.WeKickedTheirAss_Medium02'	
    TauntSounds(6)=SoundNodeWave'A_VoicePack_GEARSofWAR_Marcus.WeveGotSomeMore_Loud01'
	TauntSounds(7)=SoundNodeWave'A_VoicePack_GEARSofWAR_Marcus.WhosNext_Loud01'
	TauntSounds(8)=SoundNodeWave'A_VoicePack_GEARSofWAR_Marcus.AllClear_Loud02'
	TauntSounds(9)=SoundNodeWave'A_VoicePack_GEARSofWAR_Marcus.BackInYourHole_Loud02'
	TauntSounds(10)=SoundNodeWave'A_VoicePack_GEARSofWAR_Marcus.GoodNight_Medium02'
	TauntSounds(11)=SoundNodeWave'A_VoicePack_GEARSofWAR_Marcus.hit01'
	
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