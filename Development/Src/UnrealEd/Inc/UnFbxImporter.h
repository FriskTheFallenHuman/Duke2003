/*
* Copyright 2009 - 2010 Autodesk, Inc.  All Rights Reserved.
*
* Permission to use, copy, modify, and distribute this software in object
* code form for any purpose and without fee is hereby granted, provided
* that the above copyright notice appears in all copies and that both
* that copyright notice and the limited warranty and restricted rights
* notice below appear in all supporting documentation.
*
* AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS.
* AUTODESK SPECIFICALLY DISCLAIMS ANY AND ALL WARRANTIES, WHETHER EXPRESS
* OR IMPLIED, INCLUDING WITHOUT LIMITATION THE IMPLIED WARRANTY
* OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE OR NON-INFRINGEMENT
* OF THIRD PARTY RIGHTS.  AUTODESK DOES NOT WARRANT THAT THE OPERATION
* OF THE PROGRAM WILL BE UNINTERRUPTED OR ERROR FREE.
*
* In no event shall Autodesk, Inc. be liable for any direct, indirect,
* incidental, special, exemplary, or consequential damages (including,
* but not limited to, procurement of substitute goods or services;
* loss of use, data, or profits; or business interruption) however caused
* and on any theory of liability, whether in contract, strict liability,
* or tort (including negligence or otherwise) arising in any way out
* of such code.
*
* This software is provided to the U.S. Government with the same rights
* and restrictions as described herein.
*/

/*=============================================================================
					FBX importer for Unreal Engine 3
=============================================================================*/
#if WITH_FBX

#ifndef __UNFBXIMPORTER_H__
#define __UNFBXIMPORTER_H__

#include "Factories.h"

// Temporarily disable a few warnings due to virtual function abuse in FBX source files
#pragma warning( push )
#pragma warning( disable : 4263 ) // 'function' : member function does not override any base class virtual member function
#pragma warning( disable : 4264 ) // 'virtual_function' : no override available for virtual member function from base 'class'; function is hidden

// Include the fbx sdk header
// temp undef/redef of _O_RDONLY because kfbxcache.h (included by fbxsdk.h) does
// a weird use of these identifiers inside an enum.
#ifdef _O_RDONLY
#define TMP_UNFBX_BACKUP_O_RDONLY _O_RDONLY
#define TMP_UNFBX_BACKUP_O_WRONLY _O_WRONLY
#undef _O_RDONLY
#undef _O_WRONLY
#endif


//Robert G. : Packing was only set for the 64bits platform, but we also need it for 32bits.
//This was found while trying to trace a loop that iterate through all character links.
//The memory didn't match what the debugger displayed, obviously since the packing was not right.
#pragma pack(push,8)
	#include <fbxsdk.h>
#pragma pack(pop)


#ifdef TMP_UNFBX_BACKUP_O_RDONLY
#define _O_RDONLY TMP_FBX_BACKUP_O_RDONLY
#define _O_WRONLY TMP_FBX_BACKUP_O_WRONLY
#undef TMP_UNFBX_BACKUP_O_RDONLY
#undef TMP_UNFBX_BACKUP_O_WRONLY
#endif

#pragma warning( pop )

class FSkeletalMeshBinaryImport;
class ASkeletalMeshActor;
struct FbxSceneInfo;

namespace UnFbx
{

struct FBXImportOptions
{
	// General options
	UBOOL bImportMaterials;
	UBOOL bInvertNormalMap;
	UBOOL bImportTextures;
    UBOOL bOverrideTangents;
	// flag if import materials and textures to separate group "Materials" and "Textures"
	UBOOL bToSeparateGroup;
	UBOOL bImportLOD;
	UBOOL bUsedAsFullName;
	UBOOL bRemoveNameSpace;
	// Static Mesh options
	UBOOL bCombineToSingle;
	UBOOL bExplicitNormals;
	UBOOL bRemoveDegenerates;
	// Skeletal Mesh options
	UBOOL bImportMorph;
	UBOOL bImportAnimSet;
	UBOOL bResample;
	UBOOL bImportRigidAnim;
	UBOOL bUseT0AsRefPose;
	UBOOL bSplitNonMatchingTriangles;
};

/**
* UnrealMemoryAllocator : a custom memory allocator 
* to be used by the FBX SDK
*/ 
class UnrealFBXMemoryAllocator : public KFbxMemoryAllocator 
{
public:
	UnrealFBXMemoryAllocator() 
		: KFbxMemoryAllocator(MyMalloc, MyCalloc, MyRealloc, MyFree, MyMsize)
	{
	}

	~UnrealFBXMemoryAllocator()  
	{
	}

	static void* MyMalloc(size_t pSize)       
	{
		return malloc(pSize);
	}

	static void* MyCalloc(size_t pCount,size_t pSize)
	{
		return calloc(pCount, pSize);
	}

	static void* MyRealloc(void* pData, size_t pSize)
	{
		return realloc(pData, pSize);
	}

	static void  MyFree(void* pData)
	{
		free(pData);
	}

	static size_t MyMsize(void* pData)
	{
		return _msize(pData);
	}
};

/**
* FBX basic data conversion class.
*/
class CBasicDataConverter
{
public:

	CBasicDataConverter() 
	{}

	FVector ConvertPos(KFbxVector4 Vector);
	FVector ConvertDir(KFbxVector4 Vector);
	FVector ConvertScale(fbxDouble3 Vector);
	FVector ConvertScale(KFbxVector4 Vector);
	FRotator ConvertRotation(KFbxQuaternion Quaternion);
	FVector ConvertRotationToFVect(KFbxQuaternion Quaternion, UBOOL bInvertRot);
	FQuat ConvertRotToQuat(KFbxQuaternion Quaternion);
	FQuat ConvertRotToAnimQuat(KFbxQuaternion Quaternion, UBOOL bForAnimation);
	FLOAT ConvertDist(fbxDouble1 Distance);
	UBOOL ConvertPropertyValue(KFbxProperty& FbxProperty, UProperty& UnrealProperty, UPropertyValue& OutUnrealPropertyValue);
	
	KFbxVector4 ConvertToFbxPos(FVector Vector);
	KFbxVector4 ConvertToFbxRot(FVector Vector);
	KFbxVector4 ConvertToFbxScale(FVector Vector);
	KFbxVector4 ConvertToFbxColor(FColor Color);
};

/**
 * Main FBX Importer class.
 */
class CFbxImporter
{
public:
	/**
	 * Returns the importer singleton. It will be created on the first request.
	 */
	static CFbxImporter* GetInstance();

	/**
	 * Detect if the FBX file has skeletal mesh model. If there is deformer definition, then there is skeletal mesh.
	 * In this function, we don't need to import the scene. But the open process is time-consume if the file is large.
	 *
	 * @param InFilename	FBX file name. 
	 * @return INT -1 if parse failed; 0 if no deformer; 1 if there are deformers.
	 */
	INT DetectDeformer(const FFilename& InFilename);

	/**
	 * Get detail infomation in the Fbx scene
	 *
	 * @param Filename Fbx file name
	 * @param SceneInfo return the scene info
	 * @return UBOOL TRUE if get scene info successfully
	 */
	UBOOL GetSceneInfo(FString Filename, FbxSceneInfo& SceneInfo);
	
	/**
	 * If FBX nodes are not skeletons, but used as links, then replace them as FBX skeletons if OutLinkNodes is NULL,
	 * or fill these FBX nodes to the OutLinkNodes if OutLinkNodes is not NULL.
	 *
	 * @param Node FBX root node, we find or replace nodes recursively.
	 * @param OutLinkNodes if not NULL, fill FBX nodes that are not skeletons but used as links into this array.
	 */
	//void ReplaceOrFindNullsUsedAsLinks(KFbxNode* Node, TArray<KFbxNode*> *OutLinkNodes = NULL);

	/**
	 * Initialize Fbx file for import.
	 *
	 * @param Filename
	 * @param bParseStatistics
	 * @return UBOOL
	 */
	UBOOL OpenFile(FString Filename, UBOOL bParseStatistics);
	
	/**
	 * Import Fbx file.
	 *
	 * @param Filename
	 * @return UBOOL
	 */
	UBOOL ImportFile(FString Filename);
	
	/**
	 * Attempt to load an FBX scene from a given filename.
	 *
	 * @param Filename FBX file name to import.
	 * @returns TRUE on success.
	 */
	UBOOL ImportFromFile(const TCHAR* Filename);

	/**
	 * Retrieve the FBX loader's error message explaining its failure to read a given FBX file.
	 * Note that the message should be valid even if the parser is successful and may contain warnings.
	 *
	 * @ return TCHAR*	the error message
	 */
	const TCHAR* GetErrorMessage() const
	{
		return *ErrorMessage;
	}

	/**
	 * Retrieve the object inside the FBX scene from the name
	 *
	 * @param ObjectName	Fbx object name
	 * @param Root	Root node, retrieve from it
	 * @return KFbxNode*	Fbx object node
	 */
	KFbxNode* RetrieveObjectFromName(const TCHAR* ObjectName, KFbxNode* Root = NULL);

	/**
	 * Creates a static mesh with the given name and flags, imported from within the FBX scene.
	 * @param InParent
	 * @param Node	Fbx Node to import
	 * @param Name	the Unreal Mesh name after import
	 * @param Flags
	 * @param InStaticMesh	if LODIndex is not 0, this is the base mesh object. otherwise is NULL
	 * @param LODIndex	 LOD level to import to
	 *
	 * @returns UObject*	the UStaticMesh object.
	 */
	UObject* ImportStaticMesh(UObject* InParent, KFbxNode* Node, const FName& Name, EObjectFlags Flags, UStaticMesh* InStaticMesh = NULL, int LODIndex = 0);

	/**
	* Creates a static mesh from all the meshes in FBX scene with the given name and flags.
	*
	* @param InParent
	* @param MeshNodeArray	Fbx Nodes to import
	* @param Name	the Unreal Mesh name after import
	* @param Flags
	* @param InStaticMesh	if LODIndex is not 0, this is the base mesh object. otherwise is NULL
	* @param LODIndex	 LOD level to import to
	*
	* @returns UObject*	the UStaticMesh object.
	*/
	UObject* ImportStaticMeshAsSingle(UObject* InParent, TArray<KFbxNode*>& MeshNodeArray, const FName& Name, EObjectFlags Flags, UStaticMesh* InStaticMesh, int LODIndex = 0);

	/**
	 * re-import Unreal static mesh from updated Fbx file
	 * if the Fbx mesh is in LODGroup, the LOD of mesh will be updated
	 *
	 * @param Mesh the original Unreal static mesh object
	 * @return UObject* the new Unreal mesh object
	 */
	UObject* ReimportStaticMesh(UStaticMesh* Mesh);
	
	/**
	* re-import Unreal skeletal mesh from updated Fbx file
	* If the Fbx mesh is in LODGroup, the LOD of mesh will be updated.
	* If the FBX mesh contains morph, the morph is updated.
	* Materials, textures and animation attached in the FBX mesh will not be updated.
	*
	* @param Mesh the original Unreal skeletal mesh object
	* @return UObject* the new Unreal mesh object
	*/
	UObject* ReimportSkeletalMesh(USkeletalMesh* Mesh);

	/**
	 * Creates a skeletal mesh from Fbx Nodes with the given name and flags, imported from within the FBX scene.
	 * These Fbx Nodes bind to same skeleton. We need to bind them to one skeletal mesh.
	 *
	 * @param InParent
	 * @param NodeArray	Fbx Nodes to import
	 * @param Name	the Unreal Mesh name after import
	 * @param Flags
	 * @param Filename	Fbx file name
	 * @param FbxShapeArray	Fbx Morph objects.
	 * @param OptionalImportData	alternative weight and influence data
	 * @param OutData - Optional import data to populate
	 * @param bCreateRenderData - Whether or not skeletal mesh rendering data will be created.
	 *
	 * @return The USkeletalMesh object created
	 */
	UObject* ImportSkeletalMesh(UObject* InParent, TArray<KFbxNode*>& NodeArray, const FName& Name, EObjectFlags Flags, FString Filename, TArray<KFbxShape*> *FbxShapeArray=NULL, FSkelMeshOptionalImportData *OptionalImportData=NULL, FSkeletalMeshBinaryImport* OutData=NULL, UBOOL bCreateRenderData = TRUE );

	/**
	 * import skeletal mesh alternate weights.
	 * It pick up the first skeletal mesh from the FBX scene, then fill out the Influence data.
	 * 
	 * @param OutRawMeshInfluencesData   return the alternative weight and influence data.
	 */
	void ImportAlterWeightSkelMesh(FSkeletalMeshBinaryImport& OutRawMeshInfluencesData);

	/**
	 * Add to the animation set, the animations contained within the FBX scene, for the given skeletal mesh
	 *
	 * @param SkeletalMesh	skeletal mesh that the animation belong to
	 * @param SortedLinks	skeleton nodes which are sorted
	 * @param Filename	Fbx file name
	 * @param NodeArray node array of FBX meshes
	 * @param AnimSet	animset to import. If it is NULL, we will create an animset object
	 */
	void ImportAnimSet(USkeletalMesh* SkeletalMesh, TArray<KFbxNode*>& SortedLinks, FString Filename, TArray<KFbxNode*>& NodeArray, UAnimSet* AnimSet = NULL);

	/**
	 * Import Fbx Morph object for the Skeletal Mesh.
	 * In Fbx, morph object is a property of the Fbx Node.
	 *
	 * @param SkelMeshNodeArray - Fbx Nodes that the base Skeletal Mesh construct from
	 * @param BaseSkelMesh - base Skeletal Mesh
	 * @param Filename - Fbx file name
	 * @param LODIndex - LOD index
	 */
	void ImportFbxMorphTarget(TArray<KFbxNode*> &SkelMeshNodeArray, USkeletalMesh* BaseSkelMesh, const FFilename& Filename, INT LODIndex);

	/**
	 * Import LOD object for skeletal mesh
	 *
	 * @param InSkeletalMesh - LOD mesh object
	 * @param BaseSkeletalMesh - base mesh object
	 * @param DesiredLOD - LOD level
	 */
	void ImportSkeletalMeshLOD(USkeletalMesh* InSkeletalMesh, USkeletalMesh* BaseSkeletalMesh, INT DesiredLOD);

	/**
	 * Empties the FBX scene, releasing its memory.
	 * Currently, we can't release KFbxSdkManager because Fbx Sdk2010.2 has a bug that FBX can only has one global sdkmanager.
	 * From Fbx Sdk2011, we can create multiple KFbxSdkManager, then we can release it.
	 */
	void ReleaseScene();

	/**
	 * If the node model is a collision model, then fill it into collision model list
	 *
	 * @param Node Fbx node
	 * @return TRUE if the node is a collision model
	 */
	UBOOL FillCollisionModelList(KFbxNode* Node);

	/**
	 * Import collision models for one static mesh if it has collision models
	 *
	 * @param StaticMesh - mesh object to import collision models
	 * @param NodeName - name of Fbx node that the static mesh constructed from
	 * @return return TRUE if the static mesh has collision model and import successfully
	 */
	UBOOL ImportCollisionModels(UStaticMesh* StaticMesh, KString* NodeName);

	//help
	char* MakeName(const char* name);
	FName MakeNameForMesh(FString InName, KFbxObject* FbxObject);

	// meshes
	
	/**
	* Get all Fbx skeletal mesh objects in the scene. these meshes are grouped by skeleton they bind to
	*
	* @param Node Root node to find skeletal meshes
	* @param outSkelMeshArray return Fbx meshes they are grouped by skeleton
	*/
	void FillFbxSkelMeshArrayInScene(KFbxNode* Node, TArray< TArray<KFbxNode*>* >& outSkelMeshArray, UBOOL ExpandLOD);
	
	/**
	 * Find FBX meshes that match Unreal skeletal mesh according to the bone of mesh
	 *
	 * @param FillInMesh     Unreal skeletal mesh
	 * @param bExpandLOD     flag that if expand FBX LOD group when get the FBX node
	 * @param OutFBXMeshNodeArray  return FBX mesh nodes that match the Unreal skeletal mesh
	 * 
	 * @return the root bone that bind to the FBX skeletal meshes
	 */
	KFbxNode* FindFBXMeshesByBone(USkeletalMesh* FillInMesh, UBOOL bExpandLOD, TArray<KFbxNode*>& OutFBXMeshNodeArray);
	
	/**
	* Get mesh count (including static mesh and skeletal mesh, except collision models) and find collision models
	*
	* @param Node Root node to find meshes
	* @param FbxImporter
	* @return INT mesh count
	*/
	INT GetFbxMeshCount(KFbxNode* Node, UnFbx::CFbxImporter* FbxImporter);
	
	/**
	* Get all Fbx mesh objects
	*
	* @param Node Root node to find meshes
	* @param outMeshArray return Fbx meshes
	*/
	void FillFbxMeshArray(KFbxNode* Node, TArray<KFbxNode*>& outMeshArray, UnFbx::CFbxImporter* FbxImporter);
	
	/**
	* Fill FBX skeletons to OutSortedLinks recursively
	*
	* @param Link Fbx node of skeleton root
	* @param OutSortedLinks
	*/
	void RecursiveBuildSkeleton(KFbxNode* Link, TArray<KFbxNode*>& OutSortedLinks);

	/**
	 * Fill FBX skeletons to OutSortedLinks
	 *
	 * @param ClusterArray Fbx clusters of FBX skeletal meshes
	 * @param OutSortedLinks
	 */
	void BuildSkeletonSystem(TArray<KFbxCluster*>& ClusterArray, TArray<KFbxNode*>& OutSortedLinks);

	/**
	 * Get Unreal skeleton root from the FBX skeleton node.
	 * Mesh and dummy can be used as skeleton.
	 *
	 * @param Link one FBX skeleton node
	 */
	KFbxNode* GetRootSkeleton(KFbxNode* Link);
	
	/**
	 * Get the object of import options
	 *
	 * @return FBXImportOptions
	 */
	FBXImportOptions* GetImportOptions();

private:
	/**
	 * ActorX plug-in can export mesh and dummy as skeleton.
	 * For the mesh and dummy in the skeleton hierarchy, convert them to FBX skeleton.
	 *
	 * @param Node root skeleton node
	 */
	void RecursiveFixSkeleton(KFbxNode* Node);
	
	/**
	* Get all Fbx skeletal mesh objects which are grouped by skeleton they bind to
	*
	* @param Node Root node to find skeletal meshes
	* @param outSkelMeshArray return Fbx meshes they are grouped by skeleton
	* @param SkeletonArray
	* @param ExpandLOD flag of expanding LOD to get each mesh
	*/
	void RecursiveFindFbxSkelMesh(KFbxNode* Node, TArray< TArray<KFbxNode*>* >& outSkelMeshArray, TArray<KFbxNode*>& SkeletonArray, UBOOL ExpandLOD);
	
	/**
	* Get all Fbx rigid mesh objects which are grouped by skeleton hierarchy
	*
	* @param Node Root node to find skeletal meshes
	* @param outSkelMeshArray return Fbx meshes they are grouped by skeleton hierarchy
	* @param SkeletonArray
	* @param ExpandLOD flag of expanding LOD to get each mesh
	*/
	void RecursiveFindRigidMesh(KFbxNode* Node, TArray< TArray<KFbxNode*>* >& outSkelMeshArray, TArray<KFbxNode*>& SkeletonArray, UBOOL ExpandLOD);

	/**
	 * Import Fbx Morph object for the Skeletal Mesh.  Each morph target import processing occurs in a different thread 
	 *
	 * @param SkelMeshNodeArray - Fbx Nodes that the base Skeletal Mesh construct from
	 * @param BaseSkelMesh - base Skeletal Mesh
	 * @param MorphTargetSet - the morph target set where morph targets are imported to
	 * @param Filename - Fbx file name
	 * @param LODIndex - LOD index of the skeletal mesh
	 */
	void ImportMorphTargetsInternal( TArray<KFbxNode*>& SkelMeshNodeArray, USkeletalMesh* BaseSkelMesh, UMorphTargetSet* MorphTargetSet, const FFilename& InFilename, INT LODIndex );

public:
	// current Fbx scene we are importing. Make sure to release it after import
	KFbxScene* FbxScene;
	FBXImportOptions* ImportOptions;

private:
	enum IMPORTPHASE
	{
		NOTSTARTED,
		FILEOPENED,
		IMPORTED
	};
	
	static const FLOAT SCALE_TOLERANCE;
	
	// scene management
	CBasicDataConverter Converter;
	KFbxGeometryConverter* FbxGeometryConverter;
	KFbxSdkManager* FbxSdkManager;
	KFbxImporter* Importer;
	KFbxCamera* FbxCamera;
	IMPORTPHASE CurPhase;
	FString ErrorMessage;
	// base path of fbx file
	FString FileBasePath;
	UObject* Parent;
	// Flag that the mesh is the first mesh to import in current FBX scene
	// FBX scene may contain multiple meshes, importer can import them at one time.
	// Initialized as TRUE when start to import a FBX scene
	UBOOL bFirstMesh;
	
	/**
	 * Collision model list. The key is fbx node name
	 * If there is an collision model with old name format, the key is empty string("").
	 */
	KMap<KString, KArrayTemplate<KFbxNode* >* > CollisionModels;
	TMapBase<USkeletalMesh*, UMorphTargetSet*, FALSE> SkelMeshToMorphMap;

	CFbxImporter();
	~CFbxImporter();

	/**
	 * Set up the static mesh data from Fbx Mesh.
	 *
	 * @param FbxMesh  Fbx Mesh object
	 * @param StaticMesh Unreal static mesh object to fill data into
	 * @param LODIndex	LOD level to set up for StaticMesh
	 * @return UBOOL TRUE if set up successfully
	 */
	UBOOL BuildStaticMeshFromGeometry(KFbxMesh* FbxMesh, UStaticMesh* StaticMesh, int LODIndex = 0);
	
	/**
	 * Creates a Matinee group for a given actor within a given Matinee sequence.
	 */
	//UInterpGroupInst* CreateMatineeGroup(USeqAct_Interp* Sequence, AActor* Actor);

	// helper
	USequence* GetKismetSequence(ULevel* Level);
	/**
	 * Clean up for destroy the Importer.
	 */
	void CleanUp();
	
	//UObject* CreateObjectFromNode(KFbxNode* Node);
	//void PlaceActor(AActor* Actor, KFbxNode* Node, UBOOL bInvertOrientation = false);
	/**
	* Compute the global matrix for Fbx Node
	*
	* @param Node	Fbx Node
	* @return KFbxXMatrix*	The global transform matrix
	*/
	KFbxXMatrix ComputeTotalMatrix(KFbxNode* Node);

	// various actors, current the Fbx importer don't importe them
	/**
	 * Import Fbx light
	 *
	 * @param FbxLight fbx light object
	 * @return ALight*
	 */
	ALight* CreateLight(KFbxLight* FbxLight);	
	/**
	* Import Light detail info
	*
	* @param FbxLight
	* @param UnrealLight
	* @return  UBOOL
	*/
	UBOOL FillLightComponent(KFbxLight* FbxLight, ULightComponent* UnrealLight);
	/**
	* Import Fbx Camera object
	*
	* @param FbxCamera Fbx camera object
	* @return ACameraActor*
	*/
	ACameraActor* CreateCamera(KFbxCamera* FbxCamera);

	// meshes
	/**
	* Fill skeletal mesh data from Fbx Nodes.
	*
	* @param SkelMeshImporter object to store skeletal mesh data
	* @param FbxMesh	Fbx mesh object belonging to Node
	* @param FbxSkin	Fbx Skin object belonging to FbxMesh
	* @param FbxShape	Fbx Morph object, if not NULL, we are importing a morph object.
	* @param SortedLinks    Fbx Links(bones) of this skeletal mesh
	* @param FbxMatList  All material names of the skeletal mesh
	*
	* @returns UBOOL*	TRUE if import successfully.
	*/
    UBOOL FillSkelMeshImporterFromFbx(FSkeletalMeshBinaryImport& SkelMeshImporter, KFbxMesh* FbxMesh, KFbxSkin* FbxSkin, 
										KFbxShape* FbxShape, TArray<KFbxNode*> &SortedLinks, TArray<const char *>& FbxMatList);

	/**
	* Fill material name list data from Fbx Nodes.
	* If import material option is OFF, the API will create default material slots for the skeletal mesh.
	*
	* @param NodeArray   Fbx Nodes to import, they are bound to the same skeleton system.
	* @param SkelMeshImporter object to store skeletal mesh data.
	* @param FbxMatList  All material names of the skeletal mesh
	*/
	void ImportMaterialsForSkelMesh(TArray<KFbxNode*>& NodeArray, FSkeletalMeshBinaryImport &SkelMeshImporter, TArray<const char *>& OutFbxMatList);

	/**
	 * Import bones from skeletons that NodeArray bind to.
	 *
	 * @param NodeArray Fbx Nodes to import, they are bound to the same skeleton system
	 * @param SkelMeshImporter object to store skeletal mesh data
	 * @param OutSortedLinks return all skeletons sorted by depth traversal
	 */
	UBOOL ImportBone(TArray<KFbxNode*>& NodeArray, FSkeletalMeshBinaryImport &SkelMeshImporter, TArray<KFbxNode*> &OutSortedLinks);
	
	void SetRefPoseAsT0(FSkeletalMeshBinaryImport &SkelMeshImporter, KFbxMesh* FbxMesh);
	
	// anims
	/**
	 * Check if the Fbx node contains animation
	 *
	 * @param Node Fbx node
	 * @return UBOOL TRUE if the Fbx node contains animation.
	 */
	//UBOOL IsAnimated(KFbxNode* Node);

	/**
	* Fill each Trace for AnimSequence with Fbx skeleton animation by key
	*
	* @param Node   Fbx skeleton node
	* @param AnimSequence
	* @param TakeName
	* @param bIsRoot if the Fbx skeleton node is root skeleton
	* @param Scale scale factor for this skeleton node
	*/
	UBOOL FillAnimSequenceByKey(KFbxNode* Node, UAnimSequence* AnimSequence, const char* TakeName, KTime& Start, KTime&End, UBOOL bIsRoot, KFbxVector4 Scale);
	/*UBOOL CreateMatineeSkeletalAnimation(ASkeletalMeshActor* Actor, UAnimSet* AnimSet);
	bool CreateMatineeAnimation(KFbxNode* Node, AActor* Actor, UBOOL bInvertOrient, UBOOL bAddDirectorTrack);*/


	// material
	/**
	 * Import each material Input from Fbx Material
	 *
	 * @param FbxMaterial	Fbx material object
	 * @param UnrealMaterial
	 * @param MaterialProperty The material component to import
	 * @param MaterialInput
	 * @param bSetupAsNormalMap
	 * @param UVSet
	 * @return UBOOL	
	 */
	UBOOL CreateAndLinkExpressionForMaterialProperty(	KFbxSurfaceMaterial& FbxMaterial,
														UMaterial* UnrealMaterial,
														const char* MaterialProperty ,
														FExpressionInput& MaterialInput, 
														UBOOL bSetupAsNormalMap,
														TArray<FString>& UVSet );
	/**
	 * Add a basic white diffuse color if no expression is linked to diffuse input.
	 *
	 * @param unMaterial Unreal material object.
	 */
	void FixupMaterial(UMaterial* unMaterial);
	
	/**
	 * Get material mapping array according "Skinxx" flag in material name
	 *
	 * @param FSkeletalMeshBinaryImport& The unreal skeletal mesh.
	 */
	void SetMaterialSkinXXOrder(FSkeletalMeshBinaryImport& SkelMeshImporter);
	
	/**
	 * Get material mapping array according "Skinxx" flag in material name
	 *
	 * @param UStaticMesh* The unreal static mesh.
	 */
	void SetMaterialSkinXXOrder(UStaticMesh* StaticMesh);

	/**
	 * Create materials from Fbx node.
	 * Only setup channels that connect to texture, and setup the UV coordinate of texture.
	 * If diffuse channel has no texture, one default node will be created with constant.
	 *
	 * @param FbxNode  Fbx node
	 * @param outMaterials Unreal Materials we created
	 * @param UVSets UV set name list
	 * @return INT material count that created from the Fbx node
	 */
	INT CreateNodeMaterials(KFbxNode* FbxNode, TArray<UMaterialInterface*>& outMaterials, TArray<FString>& UVSets);
	
	/**
	* Create Unreal material from Fbx material.
	* Only setup channels that connect to texture, and setup the UV coordinate of texture.
	* If diffuse channel has no texture, one default node will be created with constant.
	*
	* @param KFbxSurfaceMaterial*  Fbx material
	* @param outMaterials Unreal Materials we created
	* @param outUVSets
	 */
	void CreateUnrealMaterial(KFbxSurfaceMaterial* FbxMaterial, TArray<UMaterialInterface*>& OutMaterials, TArray<FString>& UVSets);
	
	/**
	 * Visit all materials of one node, import textures from materials.
	 *
	 * @param Node FBX node.
	 */
	void ImportTexturesFromNode(KFbxNode* Node);
	
	/**
	 * Generate Unreal texture object from FBX texture.
	 *
	 * @param FbxTexture FBX texture object to import.
	 * @param bSetupAsNormalMap Flag to import this texture as normal map.
	 * @return UTexture* Unreal texture object generated.
	 */
	UTexture* ImportTexture(KFbxTexture* FbxTexture, UBOOL bSetupAsNormalMap);
	
	/**
	 *
	 *
	 * @param
	 * @return UMaterial*
	 */
	//UMaterial* GetImportedMaterial(KFbxSurfaceMaterial* pMaterial);

	/**
	* Check if the meshes in FBX scene contain smoothing group info.
	* It's enough to only check one of mesh in the scene because "Export smoothing group" option affects all meshes when export from DCC.
	* To ensure only check one time, use flag bFirstMesh to record if this is the first mesh to check.
	*
	* @param FbxMesh Fbx mesh to import
	*/
	void CheckSmoothingInfo(KFbxMesh* FbxMesh);

	/**
	 * check if two faces belongs to same smoothing group
	 *
	 * @param SkelMeshImporter
	 * @param Face1 one face of the skeletal mesh
	 * @param Face2 another face
	 * @return UBOOL TRUE if two faces belongs to same group
	 */
	UBOOL FacesAreSmoothlyConnected( FSkeletalMeshBinaryImport &SkelMeshImporter, INT Face1, INT Face2 );

	/**
	 * Make un-smooth faces work.
	 *
	 * @param SkelMeshImporter
	 * @return INT number of points that added when process unsmooth faces
	*/
	INT DoUnSmoothVerts(FSkeletalMeshBinaryImport &SkelMeshImporter);
	
	/**
	 * Merge all layers of one AnimStack to one layer.
	 *
	 * @param AnimStack     AnimStack which layers will be merged
	 * @param ResampleRate  resample rate for the animation
	 */
	void MergeAllLayerAnimation(KFbxAnimStack* AnimStack, INT ResampleRate);
	
	//
	// for matinee export
	//
public:
	/**
	 * Retrieves whether there are any unknown camera instances within the FBX document.
	 */
	UBOOL HasUnknownCameras( USeqAct_Interp* MatineeSequence ) const;
	
	/**
	 * Sets the camera creation flag. Call this function before the import in order to enforce
	 * the creation of FBX camera instances that do not exist in the current UE3 scene.
	 */
	inline void SetProcessUnknownCameras(UBOOL bCreateMissingCameras)
	{
		bCreateUnknownCameras = bCreateMissingCameras;
	}
	
	/**
	 * Modifies the Matinee sequence with the animations found in the FBX document.
	 */
	void ImportMatineeSequence(USeqAct_Interp* MatineeSequence);
private:
	UBOOL bCreateUnknownCameras;
	
	/**
	 * Creates a Matinee group for a given actor within a given Matinee sequence.
	 */
	UInterpGroupInst* CreateMatineeGroup(USeqAct_Interp* MatineeSequence, AActor* Actor, FString GroupName);
	/**
	 * Imports a FBX scene node into a Matinee actor group.
	 */
	FLOAT ImportMatineeActor(KFbxNode* FbxNode, UInterpGroupInst* MatineeGroup);

	/**
	 * Imports an FBX transform curve into a movement subtrack
	 */
	void ImportMoveSubTrack( KFbxAnimCurve* FbxCurve, INT FbxDimension, UInterpTrackMoveAxis* SubTrack, INT CurveIndex, UBOOL bNegative, KFbxAnimCurve* RealCurve, FLOAT DefaultVal );

	 /**
	  * Applies pre and post rotations to a movement track
	  */
	void FixupMatineeMovementTrackRotations(UInterpTrackMove* MovementTrack, KFbxNode* FbxNode);
	 /**
	  * Applies pre and post rotations to movement subtracks
	  */
	void FixupMatineeMovementSubTrackRotations(TArray<UInterpTrackMoveAxis*>& SubTracks, KFbxNode* FbxNode);

	/**
	 * Imports a FBX animated element into a Matinee track.
	 */
	void ImportMatineeAnimated(KFbxAnimCurve* FbxCurve, INT FbxDimension, FInterpCurveVector& Curve, INT CurveIndex, UBOOL bNegative, KFbxAnimCurve* RealCurve, FLOAT DefaultVal);
	/**
	 * Imports a FBX camera into properties tracks of a Matinee group for a camera actor.
	 */
	void ImportCamera(ACameraActor* Actor, UInterpGroupInst* MatineeGroup, KFbxCamera* FbxCamera);
	/**
	 * Imports a FBX animated value into a property track of a Matinee group.
	 */
	void ImportAnimatedProperty(FLOAT* Value, const TCHAR* ValueName, UInterpGroupInst* MatineeGroup, const FLOAT FbxValue, KFbxProperty FbxProperty, UBOOL IsCameraFoV = FALSE);
	/**
	 * Check if FBX node has transform animation (translation and rotation, not check scale animation)
	 */
	UBOOL IsNodeAnimated(KFbxNode* FbxNode, KFbxAnimLayer* AnimLayer = NULL);
	/**
	 * Get Unreal Interpolation mode from FBX interpolation mode
	 */
	BYTE GetUnrealInterpMode(KFbxAnimCurveKey FbxKey);
	
};

} // namespace UnFbx

#endif // __UNFBXIMPORTER_H__

#endif // WITH_FBX
