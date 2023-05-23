/**
* Created using Unreal Script Wizard by RyanJon2040
* Visit: www.dynamiceffects.net
* Meet me on Facebook: www.facebook.com/satheeshpv
*/

class UTAttachment_GOWSniper extends UTWeaponAttachment;

DefaultProperties
{	
    Begin Object Name=SkeletalMeshComponent0
        SkeletalMesh=SkeletalMesh'WP_GOW.Mesh.WP_GOWSniper_P3'
        Scale=0.9000000
    End Object	
	
	//play pistol holding animations//
    WeapAnimType=EWAT_Default

    bMakeSplash=True

    //muzzleflash
	MuzzleFlashSocket=MuzzleFlashSocket
    MuzzleFlashPSCTemplate=ParticleSystem'WP_Enforcers.Effects.P_WP_Enforcers_3P_MuzzleFlash_fix'

    //<DO NOT MODIFY>
    Mesh=SkeletalMeshComponent0
    WeaponClass=Class'UTWeap_GOWSniper'
}