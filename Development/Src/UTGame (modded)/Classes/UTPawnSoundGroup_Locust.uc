/**
 *
 * Copyright 1998-2011 Epic Games, Inc. All Rights Reserved.
 */

class UTPawnSoundGroup_Locust extends UTPawnSoundGroup;

defaultproperties
{
	DodgeSound=SoundCue'A_Character_Locust.Dodge_Cue'
	DefaultJumpingSound=SoundCue'A_Character_Locust.Jump_Cue'
	DoubleJumpSound=SoundCue'A_Character_Locust.Jump_Cue'
	LandSound=SoundCue'A_Character_Locust.Land_Cue'
	DefaultFootStepSound=SoundCue'A_Character_Footsteps.Footsteps.A_Character_Footstep_DefaultCue'
	DyingSound=SoundCue'A_Character_Locust.b_death_Cue'
	HitSounds[0]=SoundCue'A_Character_Locust.b_pain5_Cue'
	HitSounds[1]=SoundCue'A_Character_Locust.b_pain6_Cue'
	HitSounds[2]=SoundCue'A_Character_Locust.b_pain4_Cue'
	FallingDamageLandSound=SoundCue'A_Character_Locust.Land_Cue'
	
	GibSound=SoundCue'A_Character_BodyImpacts.BodyImpacts.A_Character_BodyImpact_Bullet_Cue'
	CrushedSound=SoundCue'A_Weapon_BioRifle.Weapon.A_BioRifle_FireImpactFizzle_Cue'
	BodyExplosionSound=SoundCue'A_Weapon_BioRifle.Weapon.A_BioRifle_FireImpactExplode_Cue'
	InstaGibSound=SoundCue'A_Character_CorruptEnigma_Cue.Mean_Efforts.A_Effort_EnigmaMean_DeathInstant_Cue'
}