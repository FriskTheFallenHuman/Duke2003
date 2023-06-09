/*
* Copyright 2009 Autodesk, Inc.  All Rights Reserved.
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

#include "UnrealEd.h"

#if WITH_FBX

#include "Factories.h"
#include "Engine.h"
#include "UnTextureLayout.h"

#include "EngineMaterialClasses.h"
#include "UnFbxImporter.h"

using namespace UnFbx;

UTexture* UnFbx::CFbxImporter::ImportTexture(KFbxTexture* FbxTexture, UBOOL bSetupAsNormalMap)
{
	// create an unreal texture asset
	UTexture* UnrealTexture = NULL;
	FFilename Filename1 = ANSI_TO_TCHAR(FbxTexture->GetFileName());
	FString Extension = Filename1.GetExtension().ToLower();
	// name the texture with file name
	FString TextureName = Filename1.GetBaseFilename();

	UObject* Package;
	if (ImportOptions->bToSeparateGroup)
	{
		if (Parent == Parent->GetOutermost())
		{
			Package = Parent; // the mesh is in the outermost package
		}
		else
		{
			Package = Parent->GetOuter(); // the group of material parallels with the group of mesh
		}

		Package = Package->CreatePackage(Package, ANSI_TO_TCHAR("Textures"));
	}
	else
	{
		Package = Parent;
	}

	UBOOL AlreadyExistTexture = (FindObject<UTexture>(Package,*TextureName/*textureName.GetName()*/) != NULL);

	// try opening from absolute path
	FFilename Filename = Filename1;
	TArray<BYTE> DataBinary;
	if ( ! appLoadFileToArray( DataBinary, *Filename ))
	{
		// try fbx file base path + relative path
		FFilename Filename2 = FileBasePath + TEXT("\\") + ANSI_TO_TCHAR(FbxTexture->GetRelativeFileName());
		Filename = Filename2;
		if ( ! appLoadFileToArray( DataBinary, *Filename ))
		{
			// try fbx file base path + texture file name (no path)
			FFilename Filename3 = ANSI_TO_TCHAR(FbxTexture->GetRelativeFileName());
			FString FileOnly = Filename3.GetCleanFilename();
			Filename3 = FileBasePath + TEXT("\\") + FileOnly;
			Filename = Filename3;
			if ( ! appLoadFileToArray( DataBinary, *Filename ))
			{
				warnf(NAME_Warning,TEXT("Unable to find texture file %s. Tried:\n - %s\n - %s\n - %s"),*FileOnly,*Filename1,*Filename2,*Filename3);
			}
		}
	}
	if (DataBinary.Num()>0)
	{
		warnf(NAME_Log,TEXT("Loading texture file %s"),*Filename);
		const BYTE* PtrTexture = DataBinary.GetTypedData();
		UTextureFactory* TextureFact = new UTextureFactory;

		// save texture settings if texture exist
		TextureFact->SuppressImportOverwriteDialog();
		const TCHAR* TextureType = *Extension;

		UnrealTexture = (UTexture*)TextureFact->FactoryCreateBinary(
			UTexture2D::StaticClass(), Package, *TextureName, 
			RF_Standalone|RF_Public, NULL, TextureType, 
			PtrTexture, PtrTexture+DataBinary.Num(), GWarn );
		if(UnrealTexture)
		{
			if (bSetupAsNormalMap && !AlreadyExistTexture)
			{
				UnrealTexture->SRGB = FALSE;
				UnrealTexture->CompressionSettings = TC_Normalmap;
				UnrealTexture->LODGroup = TEXTUREGROUP_WorldNormalMap;
				UnrealTexture->UnpackMin[0] = -1.0f;
				UnrealTexture->UnpackMin[1] = -1.0f;
				UnrealTexture->UnpackMin[2] = -1.0f;
				UnrealTexture->UnpackMin[3] = 0.0f;
				UnrealTexture->UnpackMax[0] = 1.0f;
				UnrealTexture->UnpackMax[1] = 1.0f;
				UnrealTexture->UnpackMax[2] = 1.0f;
				UnrealTexture->UnpackMax[3] = 1.0f;
				if (ImportOptions->bInvertNormalMap)
				{
					UnrealTexture->UnpackMin[1] = 1.0f; 
					UnrealTexture->UnpackMax[1] = -1.0f;
				}
			}
		}
	}

	return UnrealTexture;
}

void UnFbx::CFbxImporter::ImportTexturesFromNode(KFbxNode* Node)
{
	KFbxProperty Property;
	INT NbMat = Node->GetMaterialCount();

	// visit all materials
	INT MaterialIndex;
	for (MaterialIndex = 0; MaterialIndex < NbMat; MaterialIndex++)
	{
		KFbxSurfaceMaterial *Material = Node->GetMaterial(MaterialIndex);

		//go through all the possible textures
		if(Material)
		{
			INT TextureIndex;
			FOR_EACH_TEXTURE(TextureIndex)
			{
				Property = Material->FindProperty(KFbxLayerElement::TEXTURE_CHANNEL_NAMES[TextureIndex]);

				if( Property.IsValid() )
				{
					KFbxTexture * lTexture= NULL;

					//Here we have to check if it's layered textures, or just textures:
					INT LayeredTextureCount = Property.GetSrcObjectCount(KFbxLayeredTexture::ClassId);
					KString PropertyName = Property.GetName();
					if(LayeredTextureCount > 0)
					{
						for(INT LayerIndex=0; LayerIndex<LayeredTextureCount; ++LayerIndex)
						{
							KFbxLayeredTexture *lLayeredTexture = KFbxCast <KFbxLayeredTexture>(Property.GetSrcObject(KFbxLayeredTexture::ClassId, LayerIndex));
							INT NbTextures = lLayeredTexture->GetSrcObjectCount(KFbxTexture::ClassId);
							for(INT TexIndex =0; TexIndex<NbTextures; ++TexIndex)
							{
								KFbxTexture* Texture = KFbxCast <KFbxTexture> (lLayeredTexture->GetSrcObject(KFbxTexture::ClassId,TexIndex));
								if(Texture)
								{
									ImportTexture(Texture, PropertyName == KFbxSurfaceMaterial::sNormalMap || PropertyName == KFbxSurfaceMaterial::sBump);
								}
							}
						}
					}
					else
					{
						//no layered texture simply get on the property
						INT NbTextures = Property.GetSrcObjectCount(KFbxTexture::ClassId);
						for(INT TexIndex =0; TexIndex<NbTextures; ++TexIndex)
						{

							KFbxTexture* Texture = KFbxCast <KFbxTexture> (Property.GetSrcObject(KFbxTexture::ClassId,TexIndex));
							if(Texture)
							{
								ImportTexture(Texture, PropertyName == KFbxSurfaceMaterial::sNormalMap || PropertyName == KFbxSurfaceMaterial::sBump);
							}
						}
					}
				}
			}

		}//end if(Material)

	}// end for MaterialIndex
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
UBOOL UnFbx::CFbxImporter::CreateAndLinkExpressionForMaterialProperty(
							KFbxSurfaceMaterial& FbxMaterial,
							UMaterial* UnrealMaterial,
							const char* MaterialProperty ,
							FExpressionInput& MaterialInput, 
							UBOOL bSetupAsNormalMap,
							TArray<FString>& UVSet )
{
	UBOOL bCreated = FALSE;
	
	// UDK Ultimate - MOD
	UBOOL bTwoSided = 1;
	
	KFbxProperty FbxProperty = FbxMaterial.FindProperty( MaterialProperty );
	if( FbxProperty.IsValid() )
	{
		INT LayeredTextureCount = FbxProperty.GetSrcObjectCount(KFbxLayeredTexture::ClassId);
		if (LayeredTextureCount>0)
		{
			warnf(NAME_Warning,TEXT("Layered textures are not supported (material %s)"),ANSI_TO_TCHAR(FbxMaterial.GetName()));
		}
			
		INT TextureCount = FbxProperty.GetSrcObjectCount(KFbxTexture::ClassId);
		if (TextureCount>0)
		{
			for(INT TextureIndex =0; TextureIndex<TextureCount; ++TextureIndex)
			{
				KFbxTexture* FbxTexture = FbxProperty.GetSrcObject(FBX_TYPE(KFbxTexture), TextureIndex);

				// create an unreal texture asset
				UTexture* UnrealTexture = ImportTexture(FbxTexture, bSetupAsNormalMap);
				
				if (UnrealTexture)
				{
					// and link it to the material 
					UMaterialExpressionTextureSample* UnrealTextureExpression = ConstructObject<UMaterialExpressionTextureSample>( UMaterialExpressionTextureSample::StaticClass(), UnrealMaterial );
					UnrealMaterial->Expressions.AddItem( UnrealTextureExpression );
					
					//UDK Ultimate - MOD
					UnrealMaterial->TwoSided = bTwoSided;
					
					MaterialInput.Expression = UnrealTextureExpression;
					UnrealTextureExpression->Texture = UnrealTexture;
					//UDK Ultimate - MOD

					// add/find UVSet and set it to the texture
					KString UVSetName = FbxTexture->UVSet.Get();
					FString LocalUVSetName = ANSI_TO_TCHAR(UVSetName.Buffer());
					INT SetIndex = UVSet.FindItemIndex(LocalUVSetName);
					UMaterialExpressionTextureCoordinate* MyCoordExpression = ConstructObject<UMaterialExpressionTextureCoordinate>( UMaterialExpressionTextureCoordinate::StaticClass(), UnrealMaterial );
					UnrealMaterial->Expressions.AddItem( MyCoordExpression );
					MyCoordExpression->CoordinateIndex = (SetIndex >= 0)? SetIndex: 0;
					UnrealTextureExpression->Coordinates.Expression = MyCoordExpression;

					bCreated = TRUE;
				}		
			}
		}

		if (MaterialInput.Expression)
		{
			TArray<FExpressionOutput> Outputs;
			MaterialInput.Expression->GetOutputs(Outputs);
			FExpressionOutput* Output = &Outputs(0);
			MaterialInput.Mask = Output->Mask;
			MaterialInput.MaskR = Output->MaskR;
			MaterialInput.MaskG = Output->MaskG;
			MaterialInput.MaskB = Output->MaskB;
			MaterialInput.MaskA = Output->MaskA;
		}
	}

	return bCreated;
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
void UnFbx::CFbxImporter::FixupMaterial(UMaterial* UnrealMaterial)
{
	// add a basic white diffuse color if no texture is linked to diffuse
	if (UnrealMaterial->DiffuseColor.Expression == NULL)
	{
		UMaterialExpressionVectorParameter* MyColorExpression = ConstructObject<UMaterialExpressionVectorParameter>( UMaterialExpressionVectorParameter::StaticClass(), UnrealMaterial );
		UnrealMaterial->Expressions.AddItem( MyColorExpression );
		// use random color because there may be multiple materials, then they can be different 
		MyColorExpression->DefaultValue.R = 0.5f+(0.5f*rand())/RAND_MAX;
		MyColorExpression->DefaultValue.G = 0.5f+(0.5f*rand())/RAND_MAX;
		MyColorExpression->DefaultValue.B = 0.5f+(0.5f*rand())/RAND_MAX;
		UnrealMaterial->DiffuseColor.Expression = MyColorExpression;
		TArray<FExpressionOutput> Outputs;
		UnrealMaterial->DiffuseColor.Expression->GetOutputs(Outputs);
		FExpressionOutput* Output = &Outputs(0);
		UnrealMaterial->DiffuseColor.Mask = Output->Mask;
		UnrealMaterial->DiffuseColor.MaskR = Output->MaskR;
		UnrealMaterial->DiffuseColor.MaskG = Output->MaskG;
		UnrealMaterial->DiffuseColor.MaskB = Output->MaskB;
		UnrealMaterial->DiffuseColor.MaskA = Output->MaskA;
	}
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

void UnFbx::CFbxImporter::CreateUnrealMaterial(KFbxSurfaceMaterial* FbxMaterial, TArray<UMaterialInterface*>& OutMaterials, TArray<FString>& UVSets)
{
	FString MaterialFullName = ANSI_TO_TCHAR(MakeName(FbxMaterial->GetName()));

	// check for a 'skinXX' suffix in the material name
	INT MaterialNameLen = appStrlen(*MaterialFullName) + 1;
	char* MaterialNameANSI = new char[MaterialNameLen];
	appStrcpyANSI(MaterialNameANSI, MaterialNameLen, TCHAR_TO_ANSI(*MaterialFullName));
	if (strlen(MaterialNameANSI) > 6)
	{
		const char* SkinXX = MaterialNameANSI + strlen(MaterialNameANSI) - 6;
		if (toupper(*SkinXX) == 'S' && toupper(*(SkinXX+1)) == 'K' && toupper(*(SkinXX+2)) == 'I' && toupper(*(SkinXX+3)) == 'N')
		{
			if (isdigit(*(SkinXX+4)) && isdigit(*(SkinXX+5)))
			{
				// remove the 'skinXX' suffix from the material name
				MaterialFullName = MaterialFullName.Left(MaterialNameLen - 7);
			}
		}
	}
	
	// set where to place the materials
	UObject* Package;
	if (ImportOptions->bToSeparateGroup)
	{
		if (Parent == Parent->GetOutermost())
		{
			Package = Parent;    // the mesh is in the outermost package
		}
		else
		{
			Package = Parent->GetOuter(); // the group of material parallels with the group of mesh
		}
		
		Package = Package->CreatePackage(Package, ANSI_TO_TCHAR("Materials"));
	}
	else
	{
		Package = Parent;
	}
	
	UMaterialInterface* UnrealMaterialInterface = FindObject<UMaterialInterface>(Package,*MaterialFullName);
	// does not override existing materials
	if (UnrealMaterialInterface != NULL)
	{
		OutMaterials.AddItem(UnrealMaterialInterface);
		return;
	}
	
	// create an unreal material asset
	UMaterialFactoryNew* MaterialFactory = new UMaterialFactoryNew;
	
	UMaterial* UnrealMaterial = (UMaterial*)MaterialFactory->FactoryCreateNew(
		UMaterial::StaticClass(), Package, *MaterialFullName, RF_Standalone|RF_Public, NULL, GWarn );
	// TODO :  need this ? UnrealMaterial->bUsedWithStaticLighting = TRUE;

	// textures and properties
	CreateAndLinkExpressionForMaterialProperty( *FbxMaterial, UnrealMaterial, KFbxSurfaceMaterial::sDiffuse, UnrealMaterial->DiffuseColor, FALSE, UVSets);
	CreateAndLinkExpressionForMaterialProperty( *FbxMaterial, UnrealMaterial, KFbxSurfaceMaterial::sDiffuseFactor, UnrealMaterial->DiffusePower, FALSE, UVSets);
	CreateAndLinkExpressionForMaterialProperty( *FbxMaterial, UnrealMaterial, KFbxSurfaceMaterial::sEmissive, UnrealMaterial->EmissiveColor, FALSE, UVSets);
	CreateAndLinkExpressionForMaterialProperty( *FbxMaterial, UnrealMaterial, KFbxSurfaceMaterial::sSpecular, UnrealMaterial->SpecularColor, FALSE, UVSets);
	CreateAndLinkExpressionForMaterialProperty( *FbxMaterial, UnrealMaterial, KFbxSurfaceMaterial::sSpecularFactor, UnrealMaterial->SpecularColor, FALSE, UVSets); // SpecularFactor modulates the SpecularColor value if there's one
	CreateAndLinkExpressionForMaterialProperty( *FbxMaterial, UnrealMaterial, KFbxSurfaceMaterial::sShininess, UnrealMaterial->SpecularPower, FALSE, UVSets);
	if (!CreateAndLinkExpressionForMaterialProperty( *FbxMaterial, UnrealMaterial, KFbxSurfaceMaterial::sNormalMap, UnrealMaterial->Normal, TRUE, UVSets))
	{
		CreateAndLinkExpressionForMaterialProperty( *FbxMaterial, UnrealMaterial, KFbxSurfaceMaterial::sBump, UnrealMaterial->Normal, TRUE, UVSets); // no bump in unreal, use as normal map
	}
	//CreateAndLinkExpressionForMaterialProperty( *FbxMaterial, UnrealMaterial, KFbxSurfaceMaterial::sTransparentColor, UnrealMaterial->Opacity, FALSE, UVSets);
	//CreateAndLinkExpressionForMaterialProperty( *FbxMaterial, UnrealMaterial, KFbxSurfaceMaterial::sTransparencyFactor, UnrealMaterial->OpacityMask, FALSE, UVSets);
	FixupMaterial(UnrealMaterial); // add random diffuse if none exists

	// compile shaders for PC (from UPrecompileShadersCommandlet::ProcessMaterial
	// and WxMaterialEditor::UpdateOriginalMaterial)

	//remove any memory copies of shader files, so they will be reloaded from disk
	//this way the material editor can be used for quick shader iteration
	FlushShaderFileCache();

	// make sure that any static meshes, etc using this material will stop using the FMaterialResource of the original 
	// material, and will use the new FMaterialResource created when we make a new UMaterial in place
	FGlobalComponentReattachContext RecreateComponents;
	
	// let the material update itself if necessary
	UnrealMaterial->PreEditChange(NULL);
		UnrealMaterial->PostEditChange();
	
	OutMaterials.AddItem(UnrealMaterial);
}

INT UnFbx::CFbxImporter::CreateNodeMaterials(KFbxNode* FbxNode, TArray<UMaterialInterface*>& OutMaterials, TArray<FString>& UVSets)
{
	INT MaterialCount = FbxNode->GetMaterialCount();
	for(INT MaterialIndex=0; MaterialIndex < MaterialCount; ++MaterialIndex)
	{
		KFbxSurfaceMaterial *FbxMaterial = FbxNode->GetMaterial(MaterialIndex);

		CreateUnrealMaterial(FbxMaterial, OutMaterials, UVSets);
	}
	return MaterialCount;
}


	
#endif // WITH_FBX
