/**
* Created using Unreal Script Wizard by RyanJon2040
* Visit: www.dynamiceffects.net
* Meet me on Facebook: www.facebook.com/satheeshpv
*/

class UTAmmo_Stinger extends UTAmmoPickupFactory;

DefaultProperties
{

    Begin Object Name=AmmoMeshComp
        StaticMesh=StaticMesh'WP_GOW.Mesh.stinger_ammo'
        Translation=(X=0.0,Y=0.0,Z=-16.0)
    End Object

    Begin Object Name=CollisionCylinder
        CollisionHeight=14.4
    End Object

    AmmoAmount=25
	Drawscale=0.40

    //PickupSound=SoundCue'WP_Enforcers.Sounds.A_Weapon_Enforcer_ReloadComposite01_Cue'

    //<DO NOT MODIFY>
    TargetWeapon=Class'UTWeap_Stinger'
}
