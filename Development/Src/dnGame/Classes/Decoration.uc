//=============================================================================
// Decoration.
//=============================================================================
class Decoration extends Pawn
	abstract
	placeable
	native;

// If set, the pyrotechnic or explosion when item is damaged.
var()  class<actor> EffectWhenDestroyed;
var() bool bPushable;
var() bool bDamageable;
var bool bPushSoundPlaying;
var bool bSplash;

var() SoundCue PushSound, EndPushSound;
var const int	 numLandings;		// Used by engine physics.
var() class<inventory> contents;	// spawned when destroyed

var()	int		NumFrags;		// number of fragments to spawn when destroyed
var()	texture	FragSkin;		// skin to use for fragments
//var()	class<Fragment> FragType;	// type of fragment to use
var		vector FragMomentum;		// momentum to be imparted to frags when destroyed
var()	int		Health;
var()	float  SplashTime;

//var const NavigationPoint LastAnchor;		// recent nearest path
var		float	LastValidAnchorTime;	// last time a valid anchor was found

event NotReachableBy(Pawn P); // called when FindPathToward this decoration fails (used by GameObjects)

function bool CanSplash()
{
	if ( (WorldInfo.TimeSeconds - SplashTime > 0.25) && (Physics == PHYS_Falling) && (Abs(Velocity.Z) > 100) )
	{
		SplashTime = WorldInfo.TimeSeconds;
		return true;
	}
	return false;
}

function Drop(vector newVel);

simulated function Landed(vector HitNormal, Actor FloorActor)
{
	local rotator NewRot;
	local Pawn localOwner;

	localOwner = Pawn(Owner);

	if (Velocity.Z<-500) 
		TakeDamage(100,localOwner.Controller,FloorActor.Location,HitNormal,class'Crushed');	
	Velocity = vect(0,0,0);
	NewRot = Rotation;
	NewRot.Pitch = 0;
	NewRot.Roll = 0;
	SetRotation(NewRot);
}

event HitWall( vector HitNormal, actor Wall, PrimitiveComponent WallComp )
{
	Landed(HitNormal, Wall);
}

function TakeDamage(int DamageAmount, Controller EventInstigator, vector HitLocation, vector Momentum, class<DamageType> damageType, optional TraceHitInfo HitInfo, optional Actor DamageCauser)
{
	Instigator = PlayerController(EventInstigator).Pawn;
	if (!bDamageable || (Health<0) ) 
		Return;
	if ( Instigator != None )
		MakeNoise(1.0);
	Health -= DamageAmount;
	FragMomentum = Momentum;
	if (Health <0) 	
		Destroy();		
	else 
	{
		SetPhysics(PHYS_Falling);
		Momentum.Z = 1000;
		Velocity=Momentum/Mass;
	}
}

singular function PhysicsVolumeChange( PhysicsVolume NewVolume )
{
	if( NewVolume.bWaterVolume )
	{
		if( bSplash && !PhysicsVolume.bWaterVolume && Mass<=Buoyancy 
			&& ((Abs(Velocity.Z) < 100) || (Mass == 0)) && (FRand() < 0.05) && !PlayerCanSeeMe() )
		{
			bSplash = false;
			SetPhysics(PHYS_None);
		}
	}
	if( PhysicsVolume.bWaterVolume && (Buoyancy > Mass) )
	{
		if( Buoyancy > 1.1 * Mass )
			Buoyancy = 0.95 * Buoyancy; // waterlog
		else if( Buoyancy > 1.03 * Mass )
			Buoyancy = 0.99 * Buoyancy;
	}
}

function Trigger( actor Other, pawn EventInstigator )
{
	Instigator = EventInstigator;
	TakeDamage( 1000, Instigator.Controller, Location, Vect(0,0,1)*900, class'Crushed');
}

singular function BaseChange()
{
	if( Velocity.Z < -500 )
		TakeDamage( (1-Velocity.Z/30),Instigator.Controller,Location,vect(0,0,0) , class'Crushed');

	if( base == None )
	{ 
		if ( /*!bInterpolating &&*/ bPushable && (Physics == PHYS_None) )
			SetPhysics(PHYS_Falling);
	}
	else if( Pawn(Base) != None )
	{
		Base.TakeDamage( (1-Velocity.Z/400)* mass/Pawn(Base).Mass,Instigator.Controller,Location,0.5 * Velocity , class'Crushed');
		Velocity.Z = 100;
		if (FRand() < 0.5)
			Velocity.X += 70;
		else
			Velocity.Y += 70;
		SetPhysics(PHYS_Falling);
	}
	else if( Decoration(Base)!=None && Velocity.Z<-500 )
	{
		Base.TakeDamage((1 - Mass/Pawn(Base).Mass * Velocity.Z/30), Instigator.Controller, Location, 0.2 * Velocity, class'Crushed');
		Velocity.Z = 100;
		if (FRand() < 0.5)
			Velocity.X += 70;
		else
			Velocity.Y += 70;
		SetPhysics(PHYS_Falling);
	}
	else
		instigator = None;
}

simulated function Destroyed()
{
	local inventory dropped;
	local int i;
	// local Fragment s;
	local float BaseSize;
	local vector vel;
	
	vel.X = 0;
	vel.Y = 0;
	vel.Z = 0;

	if ( Role == ROLE_Authority )
	{
		if( (Contents!=None) && !WorldInfo.bStartup )
		{
			dropped = Spawn(Contents);
			dropped.DropFrom(Location, vel);
		}	

		//TriggerEvent( Event, Self, None);

		if ( bPushSoundPlaying )
			PlaySound(EndPushSound);
	}
/*		
	if ( (Level.NetMode != NM_DedicatedServer ) 
		&& !PhysicsVolume.bDestructive
		&& (NumFrags > 0) && (FragType != None) )
	{
		// spawn fragments
		BaseSize = 0.8 * sqrt(CollisionRadius*CollisionHeight)/NumFrags;
		for ( i=0; i<numfrags; i++ )
		{
			s = Spawn( FragType, Owner,,Location + CollisionRadius * VRand());
			s.CalcVelocity(FragMomentum);
			if ( FragSkin != None )
				s.Skins[0] = FragSkin;
			s.SetDrawScale(BaseSize * (0.5+0.7*FRand()));
		}
	}
*/
	Super.Destroyed();
}

function Timer()
{
	PlaySound(EndPushSound);
	bPushSoundPlaying=False;
}

event Bump( Actor Other2, PrimitiveComponent OtherComp, Vector HitNormal )
{
	local float speed, oldZ;
	local Pawn Other;

	if(Pawn(Other2) == None)
		return;

	Other = Pawn(Other2);

	if( bPushable && Other.Mass > 40 ) // I cleaned up this branch marking this as modified.
	{
		oldZ = Velocity.Z;
		speed = VSize(Other.Velocity);
		Velocity = Other.Velocity * FMin(120.0, 20 + speed)/speed;
		if ( Physics == PHYS_None ) 
		{
			Velocity.Z = 25;
			if (!bPushSoundPlaying) 
			{
				PlaySound(PushSound);
				bPushSoundPlaying = True;
			}			
		}
		else
			Velocity.Z = oldZ;
		SetPhysics(PHYS_Falling);
		SetTimer(0.3,False);
		Instigator = Other;
	}
}

defaultproperties
{
	bCanBeDamaged=true
     bStatic=True
     bStasis=True
     Mass=100.000000
     DrawType=DT_Mesh
	 bOrientOnSlope=true
	 bShouldBaseAtStartup=true
	 NetUpdateFrequency=10
}
