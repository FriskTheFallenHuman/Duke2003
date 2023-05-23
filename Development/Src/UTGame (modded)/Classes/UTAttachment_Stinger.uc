/**
 * Copyright 1998-2008 Epic Games, Inc. All Rights Reserved.
 */
class UTAttachment_Stinger extends UTWeaponAttachment;

defaultproperties
{

	// Weapon SkeletalMesh
	Begin Object Name=SkeletalMeshComponent0
		SkeletalMesh=SkeletalMesh'WP_Stinger.Mesh.SK_WP_Stinger_3P_Mid'
		//Translation=(X=0,Y=0)
		AnimSets[0]=AnimSet'WP_Stinger.Anims.K_WP_Stinger_3P_Base'
	End Object

	WeapAnimType=EWAT_Stinger

	bMakeSplash=true

	//BulletWhip=SoundCue'A_Weapon.Enforcers.Cue.A_Weapon_Enforcers_BulletWhizz_Cue'
	WeaponClass=class'UTWeap_Stinger'
	
    //muzzleflash
	MuzzleFlashSocket=MuzzleFlashSocket
    MuzzleFlashPSCTemplate=ParticleSystem'WP_Enforcers.Effects.P_WP_Enforcers_3P_MuzzleFlash_fix'

	FireAnim=WeaponFire
}
