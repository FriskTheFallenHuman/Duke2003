// PlayerPawn.uc
//

class PlayerPawn extends UTPawn
	nativereplication
	native;

simulated function vector WeaponBob(float BobDamping, float JumpDamping)
{
	return WalkBob;
}

function PlayTeleportEffect(bool bOut, bool bSound)
{

}