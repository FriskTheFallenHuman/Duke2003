/*===========================================================================
    C++ class definitions exported from UnrealScript.
    This is automatically generated by the tools.
    DO NOT modify this manually! Edit the corresponding .uc files instead!
    Copyright 1998-2011 Epic Games, Inc. All Rights Reserved.
===========================================================================*/
#if SUPPORTS_PRAGMA_PACK
#pragma pack (push,4)
#endif

#include "UnrealEdNames.h"

// Split enums from the rest of the header so they can be included earlier
// than the rest of the header file by including this file twice with different
// #define wrappers. See Engine.h and look at EngineClasses.h for an example.
#if !NO_ENUMS && !defined(NAMES_ONLY)

#ifndef INCLUDED_UNREALED_CASCADE_ENUMS
#define INCLUDED_UNREALED_CASCADE_ENUMS 1


#endif // !INCLUDED_UNREALED_CASCADE_ENUMS
#endif // !NO_ENUMS

#if !ENUMS_ONLY

#ifndef NAMES_ONLY
#define AUTOGENERATE_FUNCTION(cls,idx,name)
#endif


#ifndef NAMES_ONLY

#ifndef INCLUDED_UNREALED_CASCADE_CLASSES
#define INCLUDED_UNREALED_CASCADE_CLASSES 1
#define ENABLE_DECLARECLASS_MACRO 1
#include "UnObjBas.h"
#undef ENABLE_DECLARECLASS_MACRO

class UCascadeParticleSystemComponent : public UParticleSystemComponent
{
public:
    //## BEGIN PROPS CascadeParticleSystemComponent
    class FCascadePreviewViewportClient* CascadePreviewViewportPtr;
    //## END PROPS CascadeParticleSystemComponent

    DECLARE_CLASS(UCascadeParticleSystemComponent,UParticleSystemComponent,0,UnrealEd)
	// Collision Handling...
	virtual UBOOL SingleLineCheck(FCheckResult& Hit, AActor* SourceActor, const FVector& End, const FVector& Start, DWORD TraceFlags, const FVector& Extent);
};

#undef DECLARE_CLASS
#undef DECLARE_CASTED_CLASS
#undef DECLARE_ABSTRACT_CLASS
#undef DECLARE_ABSTRACT_CASTED_CLASS
#endif // !INCLUDED_UNREALED_CASCADE_CLASSES
#endif // !NAMES_ONLY


#ifndef NAMES_ONLY
#undef AUTOGENERATE_FUNCTION
#endif

#ifdef STATIC_LINKING_MOJO
#ifndef UNREALED_CASCADE_NATIVE_DEFS
#define UNREALED_CASCADE_NATIVE_DEFS

#define AUTO_INITIALIZE_REGISTRANTS_UNREALED_CASCADE \
	UCascadeParticleSystemComponent::StaticClass(); \

#endif // UNREALED_CASCADE_NATIVE_DEFS

#ifdef NATIVES_ONLY
#endif // NATIVES_ONLY
#endif // STATIC_LINKING_MOJO

#ifdef VERIFY_CLASS_SIZES
VERIFY_CLASS_OFFSET_NODIE(UCascadeParticleSystemComponent,CascadeParticleSystemComponent,CascadePreviewViewportPtr)
VERIFY_CLASS_SIZE_NODIE(UCascadeParticleSystemComponent)
#endif // VERIFY_CLASS_SIZES
#endif // !ENUMS_ONLY

#if SUPPORTS_PRAGMA_PACK
#pragma pack (pop)
#endif
