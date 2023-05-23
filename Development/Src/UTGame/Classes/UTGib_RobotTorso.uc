/**
 *
 * Copyright 1998-2011 Epic Games, Inc. All Rights Reserved.
 */

class UTGib_RobotTorso extends UTGib_Robot;

defaultproperties
{
	GibMeshesData[0]=(TheStaticMesh=None,TheSkelMesh=SkeletalMesh'UT3_Gibs.SK_CH_Gib_Torso',ThePhysAsset=PhysicsAsset'UT3_Gibs.SK_CH_Gib_Torso_Physics',DrawScale=1.5)

	HitSound=SoundCue'A_Character_BodyImpacts.BodyImpacts.A_Character_BodyImpact_Bullet_Cue'
}
