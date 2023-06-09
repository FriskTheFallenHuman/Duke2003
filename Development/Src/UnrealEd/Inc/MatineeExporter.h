/*=============================================================================
	COLLADA exporter for Unreal Engine 3.
	Based on Feeling Software's FCollada.
	Copyright 1998-2011 Epic Games, Inc. All Rights Reserved.
=============================================================================*/

#ifndef __MATINEEEXPORTER_H__
#define __MATINEEEXPORTER_H__

class UInterpData;
class UInterpTrackMove;
class UInterpTrackFloatProp;
class UInterpTrackVectorProp;

/**
 * Main COLLADA Exporter class.
 * Except for CImporter, consider the other classes as private.
 */
class MatineeExporter
{
public:

	/**
	 * Creates and readies an empty document for export.
	 */
	virtual void CreateDocument() = 0;
	

	void SetTrasformBaking(UBOOL bBakeTransforms)
	{
		bBakeKeys = bBakeTransforms;
	}

	/**
	 * Exports the basic scene information to the COLLADA document.
	 */
	virtual void ExportLevelMesh( ULevel* Level, USeqAct_Interp* MatineeSequence ) = 0;

	/**
	 * Exports the light-specific information for a UE3 light actor.
	 */
	virtual void ExportLight( ALight* Actor, USeqAct_Interp* MatineeSequence ) = 0;

	/**
	 * Exports the camera-specific information for a UE3 camera actor.
	 */
	virtual void ExportCamera( ACameraActor* Actor, USeqAct_Interp* MatineeSequence ) = 0;

	/**
	 * Exports the mesh and the actor information for a UE3 brush actor.
	 */
	virtual void ExportBrush(ABrush* Actor, UBOOL bConvertToStaticMesh) = 0;

	//void ExportModel(UModel* Model, FCDGeometry* ColladaGeometry, FCDGeometryInstance* ColladaInstance);

	/**
	 * Exports the mesh and the actor information for a UE3 static mesh actor.
	 */
	virtual void ExportStaticMesh( AActor* Actor, UStaticMeshComponent* StaticMeshComponent, USeqAct_Interp* MatineeSequence ) = 0;

	/**
	 * Exports the profile_COMMON information for a UE3 material.
	 */
	//FCDMaterial* ExportMaterial(UMaterial* Material);

	/**
	 * Exports the given Matinee sequence information into a COLLADA document.
	 */
	virtual void ExportMatinee(class USeqAct_Interp* MatineeSequence) = 0;

	/**
	 * Writes the COLLADA document to disk and releases it by calling the CloseDocument() function.
	 */
	virtual void WriteToFile(const TCHAR* Filename) = 0;

	/**
	 * Closes the COLLADA document, releasing its memory.
	 */
	virtual void CloseDocument() = 0;
	
	// Choose a name for this actor.
	// If the actor is bound to a Matinee sequence, we'll
	// use the Matinee group name, otherwise we'll just use the actor name.
	FString GetActorNodeName(AActor* Actor, USeqAct_Interp* MatineeSequence )
	{
		FString NodeName = Actor->GetName();
		if( MatineeSequence != NULL )
		{
			const UInterpGroupInst* FoundGroupInst = MatineeSequence->FindGroupInst( Actor );
			if( FoundGroupInst != NULL )
			{
				NodeName = FoundGroupInst->Group->GroupName.ToString();
			}
		}

		// Maya does not support dashes.  Change all dashes to underscores
		NodeName = NodeName.Replace(TEXT("-"), TEXT("_") );

		return NodeName;
	}
	
protected:

	/** When TRUE, a key will exported per frame at the set frames-per-second (FPS). */
	UBOOL bBakeKeys;
};

#endif // __MATINEEEXPORTER_H__
