/**
 * Copyright 1998-2011 Epic Games, Inc. All Rights Reserved.
 */
class UTVoice_Hofman extends UTVoice
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
	
	TauntSounds(0)=SoundNodeWave'A_VoicePack_GEARSofWAR_Hoffman.AndStayDown'
	TauntSounds(1)=SoundNodeWave'A_VoicePack_GEARSofWAR_Hoffman.AreYouSoldiersOrLittleGirls'
	TauntSounds(2)=SoundNodeWave'A_VoicePack_GEARSofWAR_Hoffman.BackInYourHole'
	TauntSounds(3)=SoundNodeWave'A_VoicePack_GEARSofWAR_Hoffman.ComeGetMe'
	TauntSounds(4)=SoundNodeWave'A_VoicePack_GEARSofWAR_Hoffman.DeadAllDead'
	TauntSounds(5)=SoundNodeWave'A_VoicePack_GEARSofWAR_Hoffman.EatDirtAndDie_02'
    TauntSounds(6)=SoundNodeWave'A_VoicePack_GEARSofWAR_Hoffman.Hahaha03'
	TauntSounds(7)=SoundNodeWave'A_VoicePack_GEARSofWAR_Hoffman.HowMuchCanTheyTake'
	TauntSounds(8)=SoundNodeWave'A_VoicePack_GEARSofWAR_Hoffman.JustDieWillYa_02'
	TauntSounds(9)=SoundNodeWave'A_VoicePack_GEARSofWAR_Hoffman.JustGettingFun'
	TauntSounds(10)=SoundNodeWave'A_VoicePack_GEARSofWAR_Hoffman.ThatWasNasty'
	TauntSounds(11)=SoundNodeWave'A_VoicePack_GEARSofWAR_Hoffman.TheyDontKnow_02'
	
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