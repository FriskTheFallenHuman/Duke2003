﻿/**
 * Copyright 1998-2007 Epic Games, Inc. All Rights Reserved.
 */

class UTDmgType_LeviathanExplosion extends UTDamageType
	abstract;

defaultproperties
{
	KillStatsName=KILLS_LEVIATHANEXPLOSION
	DeathStatsName=DEATHS_LEVIATHANEXPLOSION
	SuicideStatsName=SUICIDES_LEVIATHANEXLOSION
	DamageWeaponClass=class'UTVWeap_LeviathanPrimary'
	DamageWeaponFireMode=2
	VehicleDamageScaling=1.5
	bDestroysBarricades=true

	bKUseOwnDeathVel=true
	KDeathUpKick=700
	KDamageImpulse=20000
	KImpulseRadius=5000.0
}
