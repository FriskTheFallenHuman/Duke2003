/**
 *
 * Copyright 1998-2011 Epic Games, Inc. All Rights Reserved.
 */

class UTGib_Robot extends UTGib
	abstract;


var name CustomGibSocketName;

simulated function DoCustomGibEffects()
{
	local SkeletalMeshComponent SMC;
	local SkeletalMeshSocket SMS;

	SMC = SkeletalMeshComponent(GibMeshComp);

	if( SMC != none )
	{
		SMS = SMC.GetSocketByName( CustomGibSocketName );

		// so we know the spark exists in this MeshComponent
		if( SMS != none )
		{
			PSC_GibEffect = new(self) class'UTParticleSystemComponent';
			PSC_GibEffect.SetTemplate( PS_CustomEffect );
			SMC.AttachComponentToSocket( PSC_GibEffect, CustomGibSocketName );
		}
	}
}



defaultproperties
{
	HitSound=SoundCue'A_Character_BodyImpacts.BodyImpacts.A_Character_BodyImpact_Bullet_Cue'

	CustomGibSocketName="Spark"
	
	PS_CustomEffect=ParticleSystem'T_FX_UT3.Effects.P_FX_GibExplode'

	MITV_GibMeshTemplate=MaterialInstanceTimeVarying'CH_Gibs.Materials.MITV_CH_Gibs_Corrupt01'
}
