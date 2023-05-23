class UTProj_Enforcer extends UTProjectile;

simulated function PostBeginPlay()
{
    // force ambient sound if not vehicle game mode
    bImportantAmbientSound = !WorldInfo.bDropDetail;
    Super.PostBeginPlay();
}

defaultproperties
{
    //this is the visual representation of the bullet, which is a particle system based on the rocket launcher
	//I just changed the mesh by a bullet mesh (case) and the trail effect to simulate a bullet tracer
    ProjFlightTemplate=ParticleSystem'WP_Enforcers.Effects.Bullet_fix'
	
    ProjExplosionTemplate=ParticleSystem'WP_Enforcers.Effects.P_WP_Enforcer_Impact'
    ExplosionDecal=MaterialInstanceConstant'WP_Enforcers.Decals.MI_WP_Enforcer_Impact_Decal01'
    DecalWidth=12.0
    DecalHeight=12.0
    Speed=3000.0
    MaxSpeed=0
    Damage=50.0
	MomentumTransfer=1000
    MyDamageType=class'UTDmgType_Enforcer'
    LifeSpan=8.0
    RotationRate=(Roll=50000)
    bCollideWorld=true
    CheckRadius=42.0
    bCheckProjectileLight=true
    bWaitForEffects=true
    bAttachExplosionToVehicles=false
}