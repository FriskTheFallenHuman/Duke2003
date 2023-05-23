/**
* Created using Unreal Script Wizard by RyanJon2040
* Visit: www.dynamiceffects.net
* Meet me on Facebook: www.facebook.com/satheeshpv
*/

class UTAttachment_Enforcer extends UTWeaponAttachment;

defaultproperties
{
	// Weapon SkeletalMesh
	Begin Object Name=SkeletalMeshComponent0
        SkeletalMesh=SkeletalMesh'WP_Enforcers.Mesh.SK_WP_Enforcer_3P_Mid'
        Scale=0.9000000
	End Object
	
	//play pistol holding animations//
    WeapAnimType=EWAT_Pistol	

	MuzzleFlashSocket=MuzzleFlashSocket
	MuzzleFlashPSCTemplate=ParticleSystem'WP_Enforcers.Effects.P_WP_Enforcers_3P_MuzzleFlash_fix'
	
	WeaponClass=Class'UTWeap_Enforcer'

}
