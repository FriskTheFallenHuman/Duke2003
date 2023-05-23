class UTWeap_Enforcer extends UTWeapon;

defaultproperties
{

	//visual properties///////////////////////////////
    PlayerViewOffset=(X=-1.0,Y=0.0,Z=3.0)
	//x -> distance from camera
	//y -> horizontal position
	//z -> vertical position

    Begin Object class=AnimNodeSequence Name=MeshSequenceA
        bCauseActorAnimEnd=true
    End Object

    Begin Object Name=FirstPersonMesh
        SkeletalMesh=SkeletalMesh'WP_Enforcers.Mesh.SK_WP_Enforcers_1P'
        FOV=60
        Animations=MeshSequenceA
        AnimSets(0)=AnimSet'WP_Enforcers.Anims.K_WP_Enforcers_1P_Base'
        bForceUpdateAttachmentsInTick=True
        Scale=0.9000000
    End Object

    Begin Object Name=PickupMesh
        SkeletalMesh=SkeletalMesh'WP_Enforcers.Mesh.SK_WP_Enforcer_3P_Mid'
        Scale=0.9000000
    End Object
	
	ArmsAnimSet=AnimSet'WP_Enforcers.Anims.K_WP_Enforcers_1P_Arms'
	
	PivotTranslation=(Y=0.0)
	
	//this controls the projectile spawn position
	FireOffset=(X=0,Y=5,Z=-5)
	//x -> distance from camera
	//y -> horizontal position (negative value moves to left)
	//z -> vertical position	
	
	//visual properties///////////////////////////////

	//ammo properties
    MaxAmmoCount=50
    AmmoCount=5
    
	//weapons in udk ultimate are ballistic, i.e, they trully shoot real bullets, projectiles which are controlled by physics properties
	//here the properties of the bullet are controlled by the class UTProj_Enforcer
    WeaponFireTypes(0)=EWFT_Projectile
    WeaponProjectiles(0)=class'UTProj_Enforcer'
   
	//sounds
    WeaponEquipSnd=SoundCue'WP_Enforcers.Sounds.A_Weapon_Enforcer_Raise01_Cue'
    WeaponPutDownSnd=SoundCue'WP_Enforcers.Sounds.A_Weapon_Enforcer_Lower01_Cue'
    WeaponFireSnd(0)=SoundCue'WP_Enforcers.Sounds.Enforcer_Fire_Bullet_cue'
    PickupSound=SoundCue'WP_Enforcers.Sounds.A_Weapon_Enforcer_Raise01_Cue'

    //muzzleflash
	MuzzleFlashSocket=MuzzleFlashSocket
    MuzzleFlashPSCTemplate=ParticleSystem'WP_Enforcers.Effects.P_WP_Enforcers_MuzzleFlash_fix'

	//ammo fire speed functions///////////////////////////////
	FireInterval(0)=0.35
    FireInterval(1)=0.35
	//ammo fire speed functions///////////////////////////////

    //CrosshairImage=Copy texture from Content Browser
    CrossHairCoordinates=(U=128,V=0,UL=64,VL=64)

    //<DO NOT MODIFY>
    Mesh=FirstPersonMesh
    DroppedPickupMesh=PickupMesh
    PickupFactoryMesh=PickupMesh
    AttachmentClass=Class'UTAttachment_Enforcer'
	
//custom zoom properties to simulate iron sights effect	
DefaultProperties
{

bZoomedFireMode(0)=0
bZoomedFireMode(1)=1

ZoomedTargetFOV=35.0
ZoomedRate=9000
}
//custom zoom properties to simulate iron sights effect	
	
}