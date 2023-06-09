﻿/**
 * Copyright 1998-2007 Epic Games, Inc. All Rights Reserved.
 */
class UTVWeap_RocketTurret extends UTVehicleWeapon
		HideDropDown;

var int RocketBurstSize;
var float RocketBurstInterval;
var int RemainingRockets;

simulated function FireAmmunition()
{
	if (CurrentFireMode == 0)
	{
		// Use ammunition to fire
		ConsumeAmmo( CurrentFireMode );

		RemainingRockets = RocketBurstSize;
		ActuallyFire();

		if (AIController(Instigator.Controller) != None)
		{
			AIController(Instigator.Controller).NotifyWeaponFired(self,CurrentFireMode);
		}
	}
}

simulated function ActuallyFire()
{
	RemainingRockets--;

	// if this is the local player, play the firing effects
	PlayFiringSound();

	ProjectileFire();

	if ( RemainingRockets > 0 )
	{
		SetTimer(RocketBurstInterval, false, 'ActuallyFire');
	}
}

defaultproperties
{
	RocketBurstSize=4
	RocketBurstInterval=0.15
	WeaponFireTypes(0)=EWFT_Projectile
	FireInterval(0)=2.0
	WeaponFireSnd[0]=SoundCue'A_Weapon_RocketLauncher.Cue.A_Weapon_RL_Fire_Cue'
	WeaponFireTypes(1)=EWFT_None
	bZoomedFireMode(1)=1
	ZoomedTargetFOV=20.0
	ZoomedRate=60.0
	FireTriggerTags=(TurretFireRight, TurretFireLeft)
	AimError=600

	WeaponProjectiles(0)=class'UTProj_TurretRocket'
	VehicleClass=class'UTVehicle_ShieldedTurret_Rocket'
}
