class dnWeapon extends UTWeapon
	abstract
	native;

cpptext
{
	UBOOL Tick( FLOAT DeltaSeconds, ELevelTick TickType );
}

/**
 * This function aligns the gun model in the world
 */
simulated event SetPosition(UDKPawn Holder)
{
	local vector DrawOffset, ViewOffset, FinalSmallWeaponsOffset, FinalLocation;
	local EWeaponHand CurrentHand;
	local rotator NewRotation, FinalRotation, SpecRotation;
	local PlayerController PC;
	local vector2D ViewportSize;
	local bool bIsWideScreen;
	local vector SpecViewLoc;

	if ( !Holder.IsFirstPerson() )
		return;

	// Hide the weapon if hidden
	CurrentHand = GetHand();
	if ( bForceHidden || CurrentHand == HAND_Hidden)
	{
		Mesh.SetHidden(True);
		Holder.ArmsMesh[0].SetHidden(true);
		Holder.ArmsMesh[1].SetHidden(true);
		NewRotation = Holder.GetViewRotation();
		SetLocation(Instigator.GetPawnViewLocation() + (HiddenWeaponsOffset >> NewRotation));
		SetRotation(NewRotation);
		SetBase(Instigator);
		return;
	}

	if(bPendingShow)
	{
		SetHidden(False);
		bPendingShow = FALSE;
	}

	Mesh.SetHidden(False);

	foreach LocalPlayerControllers(class'PlayerController', PC)
	{
		LocalPlayer(PC.Player).ViewportClient.GetViewportSize(ViewportSize);
		break;
	}
	bIsWideScreen = (ViewportSize.Y > 0.f) && (ViewportSize.X/ViewportSize.Y > 1.7);

	// Adjust for the current hand
	ViewOffset = PlayerViewOffset;
	FinalSmallWeaponsOffset = SmallWeaponsOffset;

	switch ( CurrentHand )
	{
		case HAND_Left:
			Mesh.SetScale3D(default.Mesh.Scale3D * vect(1,-1,1));
			Mesh.SetRotation(rot(0,0,0) - default.Mesh.Rotation);
			if (ArmsAnimSet != None)
			{
				Holder.ArmsMesh[0].SetScale3D(Holder.default.ArmsMesh[0].Scale3D * vect(1,-1,1));
				Holder.ArmsMesh[1].SetScale3D(Holder.default.ArmsMesh[1].Scale3D * vect(1,-1,1));
			}
			ViewOffset.Y *= -1.0;
			FinalSmallWeaponsOffset.Y *= -1.0;
			break;

		case HAND_Centered:
			ViewOffset.Y = 0.0;
			FinalSmallWeaponsOffset.Y = 0.0;
			break;

		case HAND_Right:
			Mesh.SetScale3D(default.Mesh.Scale3D);
			Mesh.SetRotation(default.Mesh.Rotation);
			if (ArmsAnimSet != None)
			{
				Holder.ArmsMesh[0].SetScale3D(Holder.default.ArmsMesh[0].Scale3D);
				Holder.ArmsMesh[1].SetScale3D(Holder.default.ArmsMesh[1].Scale3D);
			}
			break;
		default:
			break;
	}

	if ( bIsWideScreen )
	{
		ViewOffset += WideScreenOffsetScaling * FinalSmallWeaponsOffset;
		if ( bSmallWeapons )
		{
			ViewOffset += 0.7 * FinalSmallWeaponsOffset;
		}
	}
	else if ( bSmallWeapons )
	{
		ViewOffset += FinalSmallWeaponsOffset;
	}

	// Calculate the draw offset
	if ( Holder.Controller == None )
	{
		if ( DemoRecSpectator(PC) != None )
		{
			PC.GetPlayerViewPoint(SpecViewLoc, SpecRotation);
			DrawOffset = ViewOffset >> SpecRotation;
			DrawOffset += UTPawn(Holder).WeaponBob(BobDamping, JumpDamping);
			FinalLocation = SpecViewLoc + DrawOffset;
			SetLocation(FinalLocation);
			SetBase(Holder);

			// Add some rotation leading
			SpecRotation.Yaw = LagRot(SpecRotation.Yaw & 65535, LastRotation.Yaw & 65535, MaxYawLag, 0);
			SpecRotation.Pitch = LagRot(SpecRotation.Pitch & 65535, LastRotation.Pitch & 65535, MaxPitchLag, 1);
			LastRotUpdate = WorldInfo.TimeSeconds;
			LastRotation = SpecRotation;

			if ( bIsWideScreen )
			{
				SpecRotation += WidescreenRotationOffset;
			}
			SetRotation(SpecRotation);
			return;
		}
		else
		{
		DrawOffset = (ViewOffset >> Holder.GetBaseAimRotation()) + UTPawn(Holder).GetEyeHeight() * vect(0,0,1);
	}
	}
	else
	{
		DrawOffset.Z = UTPawn(Holder).GetEyeHeight();
		DrawOffset += UTPawn(Holder).WeaponBob(BobDamping, JumpDamping);

		if ( UTPlayerController(Holder.Controller) != None )
		{
			DrawOffset += UTPlayerController(Holder.Controller).ShakeOffset >> Holder.Controller.Rotation;
		}

		DrawOffset = DrawOffset + ( ViewOffset >> Holder.Controller.Rotation );
	}

	// Adjust it in the world
	FinalLocation = Holder.Location + DrawOffset;
	SetLocation(FinalLocation);
	SetBase(Holder);

	if (ArmsAnimSet != None)
	{
		Holder.ArmsMesh[0].SetTranslation(DrawOffset);
		Holder.ArmsMesh[1].SetTranslation(DrawOffset);
	}

	NewRotation = (Holder.Controller == None) ? Holder.GetBaseAimRotation() : Holder.Controller.Rotation;

	// Add some rotation leading
	FinalRotation = NewRotation;
	LastRotUpdate = WorldInfo.TimeSeconds;
	LastRotation = NewRotation;

	if ( bIsWideScreen )
	{
		FinalRotation += WidescreenRotationOffset;
	}
	SetRotation(FinalRotation);
	if (ArmsAnimSet != None)
	{
		Holder.ArmsMesh[0].SetRotation(FinalRotation);
		Holder.ArmsMesh[1].SetRotation(FinalRotation);
	}
}