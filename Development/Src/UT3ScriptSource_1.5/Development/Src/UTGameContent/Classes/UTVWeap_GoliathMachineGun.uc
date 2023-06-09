﻿/**
 * Copyright 1998-2007 Epic Games, Inc. All Rights Reserved.
 */
class UTVWeap_GoliathMachineGun extends UTVehicleWeapon
	HideDropDown;

defaultproperties
{
 	WeaponFireTypes(0)=EWFT_InstantHit
 	WeaponFireTypes(1)=EWFT_None
	bInstantHit=true
	bFastRepeater=true
	InstantHitDamageTypes(0)=class'UTDmgType_GoliathMachineGun'

	BulletWhip=SoundCue'A_Weapon.Enforcers.Cue.A_Weapon_Enforcers_BulletWhizz_Cue'

	FireInterval(0)=+0.1
	FireInterval(1)=+0.1
	Spread(0)=0.05
	Spread(1)=0.05

	InstantHitDamage(0)=16
	InstantHitDamage(1)=16

	ShotCost(0)=0
	ShotCost(1)=0

	DefaultImpactEffect=(ParticleTemplate=ParticleSystem'VH_Goliath.EffectS.PS_Goliath_Gun_Impact',Sound=SoundCue'A_Weapon_Enforcer.Cue.A_Weapon_Enforcer_ImpactDirt_Cue',DecalMaterials=(MaterialInterface'VH_Goliath.Decals.MIC_VH_Goliath_Impact_Decal01'),DecalWidth=16.0,DecalHeight=16.0)

	FireTriggerTags=(GoliathMachineGun)

	bZoomedFireMode(0)=0
	bZoomedFireMode(1)=1

	ZoomedTargetFOV=33.0
	ZoomedRate=60.0
	AimError=600
	VehicleClass=class'UTVehicle_Goliath_Content'
}
