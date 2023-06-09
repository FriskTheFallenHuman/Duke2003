class Pistol extends dnWeapon
	native;

defaultproperties
{
	WeaponColor=(R=255,G=255,B=0,A=255)
	FireInterval(0)=+0.24
	FireInterval(1)=+0.35
	PlayerViewOffset=(X=0,Y=0,Z=0)

	Begin Object class=AnimNodeSequence Name=MeshSequenceA
		bCauseActorAnimEnd=true
	End Object

	// Weapon SkeletalMesh
	Begin Object Name=FirstPersonMesh
		SkeletalMesh=SkeletalMesh'wp_pistol.WP_PistolMesh'
		AnimSets(0)=AnimSet'wp_pistol.WP_PistolMesh_Anims'
		Animations=MeshSequenceA
		Scale=0.9
		FOV=50.0
	End Object

	WeaponFireAnim(0)=PistolFire
	WeaponFireAnim(1)=PistolFire
	ArmFireAnim(0)=PistolFire
	ArmFireAnim(1)=PistolFire

	WeaponPutDownAnim=PistolIdle
	ArmsPutDownAnim=PistolIdle
	WeaponEquipAnim=PistolIdle
	ArmsEquipAnim=PistolIdle
	WeaponIdleAnims(0)=PistolIdle
	ArmIdleAnims(0)=PistolIdle

	AmmoCount=100
	LockerAmmoCount=100
	MaxAmmoCount=100
	MomentumTransfer=50000.0
	BeamAmmoUsePerSecond=8.5
	MinimumDamage=5.0

	BobDamping=1.0
}