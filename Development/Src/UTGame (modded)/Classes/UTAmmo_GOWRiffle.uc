/**
* Created using Unreal Script Wizard by RyanJon2040
* Visit: www.dynamiceffects.net
* Meet me on Facebook: www.facebook.com/satheeshpv
*/

class UTAmmo_GOWRiffle extends UTAmmoPickupFactory;

DefaultProperties
{

    Begin Object Name=AmmoMeshComp
        StaticMesh=StaticMesh'Pickups.Ammo_Stinger.Mesh.stinger_ammo'
        Translation=(X=0.0,Y=0.0,Z=-16.0)
    End Object

    Begin Object Name=CollisionCylinder
        CollisionHeight=14.4
    End Object

    AmmoAmount=25
	Drawscale=0.40

    PickupSound=SoundCue'WP_GOW.Sounds.CogRifleClipPickup01_Cue'

    //<DO NOT MODIFY>
    TargetWeapon=Class'UTWeap_GOWRiffle'
}
