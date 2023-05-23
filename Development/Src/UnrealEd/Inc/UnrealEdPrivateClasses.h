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

#ifndef INCLUDED_UNREALED_PRIVATE_ENUMS
#define INCLUDED_UNREALED_PRIVATE_ENUMS 1


#endif // !INCLUDED_UNREALED_PRIVATE_ENUMS
#endif // !NO_ENUMS

#if !ENUMS_ONLY

#ifndef NAMES_ONLY
#define AUTOGENERATE_FUNCTION(cls,idx,name)
#endif


#ifndef NAMES_ONLY

#ifndef INCLUDED_UNREALED_PRIVATE_CLASSES
#define INCLUDED_UNREALED_PRIVATE_CLASSES 1
#define ENABLE_DECLARECLASS_MACRO 1
#include "UnObjBas.h"
#undef ENABLE_DECLARECLASS_MACRO

struct FPropertyItemCustomProxy
{
    FStringNoInit PropertyPathName;
    FStringNoInit PropertyItemClassName;
    BITFIELD bReplaceArrayHeaders:1;
    BITFIELD bIgnoreArrayElements:1;
    class UClass* PropertyItemClass;

    /** Constructors */
    FPropertyItemCustomProxy() {}
    FPropertyItemCustomProxy(EEventParm)
    {
        appMemzero(this, sizeof(FPropertyItemCustomProxy));
    }
};

struct FPropertyTypeCustomProxy
{
    FName PropertyName;
    FStringNoInit PropertyObjectClassPathName;
    FStringNoInit PropertyItemClassName;
    BITFIELD bReplaceArrayHeaders:1;
    BITFIELD bIgnoreArrayElements:1;
    class UClass* PropertyItemClass;

    /** Constructors */
    FPropertyTypeCustomProxy() {}
    FPropertyTypeCustomProxy(EEventParm)
    {
        appMemzero(this, sizeof(FPropertyTypeCustomProxy));
    }
};

struct FPropertyItemCustomClass
{
    FStringNoInit PropertyPathName;
    FStringNoInit PropertyItemClassName;
    BITFIELD bReplaceArrayHeaders:1;
    BITFIELD bIgnoreArrayElements:1;
    SCRIPT_ALIGN;
    class wxClassInfo* WxPropertyItemClass;

    /** Constructors */
    FPropertyItemCustomClass() {}
    FPropertyItemCustomClass(EEventParm)
    {
        appMemzero(this, sizeof(FPropertyItemCustomClass));
    }
};

struct FPropertyTypeCustomClass
{
    FName PropertyName;
    FStringNoInit PropertyObjectClassPathName;
    FStringNoInit PropertyItemClassName;
    BITFIELD bReplaceArrayHeaders:1;
    BITFIELD bIgnoreArrayElements:1;
    SCRIPT_ALIGN;
    class wxClassInfo* WxPropertyItemClass;

    /** Constructors */
    FPropertyTypeCustomClass() {}
    FPropertyTypeCustomClass(EEventParm)
    {
        appMemzero(this, sizeof(FPropertyTypeCustomClass));
    }
};

class UCustomPropertyItemBindings : public UObject
{
public:
    //## BEGIN PROPS CustomPropertyItemBindings
    TArrayNoInit<struct FPropertyItemCustomClass> CustomPropertyClasses;
    TArrayNoInit<struct FPropertyTypeCustomClass> CustomPropertyTypeClasses;
    TArrayNoInit<struct FPropertyItemCustomProxy> CustomPropertyDrawProxies;
    TArrayNoInit<struct FPropertyItemCustomProxy> CustomPropertyInputProxies;
    TArrayNoInit<struct FPropertyTypeCustomProxy> CustomPropertyTypeDrawProxies;
    TArrayNoInit<struct FPropertyTypeCustomProxy> CustomPropertyTypeInputProxies;
    //## END PROPS CustomPropertyItemBindings

    DECLARE_CLASS(UCustomPropertyItemBindings,UObject,0|CLASS_Config,UnrealEd)
    static const TCHAR* StaticConfigName() {return TEXT("Editor");}

	/**
	 * Returns the custom draw proxy class that should be used for the property associated with
	 * the WxPropertyControl specified.
	 *
	 * @param	ProxyOwnerItem	the property window item that will be using this draw proxy
	 * @param	ArrayIndex		specifies which element of an array property that this property window will represent.  Only valid
	 *							when creating property window items for individual elements of an array.
	 *
	 * @return	a pointer to a child of UPropertyDrawProxy that should be used as the draw proxy
	 *			for the specified property, or NULL if there is no custom draw proxy configured for
	 *			the property.
	 */
	class UClass* GetCustomDrawProxy( const class WxPropertyControl* ProxyOwnerItem, INT ArrayIndex=INDEX_NONE );

	/**
	 * Returns the custom input proxy class that should be used for the property associated with
	 * the WxPropertyControl specified.
	 *
	 * @param	ProxyOwnerItem	the property window item that will be using this input proxy
	 * @param	ArrayIndex		specifies which element of an array property that this property window will represent.  Only valid
	 *							when creating property window items for individual elements of an array.
	 *
	 * @return	a pointer to a child of UPropertyInputProxy that should be used as the input proxy
	 *			for the specified property, or NULL if there is no custom input proxy configured for
	 *			the property.
	 */
	class UClass* GetCustomInputProxy( const class WxPropertyControl* ProxyOwnerItem, INT ArrayIndex=INDEX_NONE );

	/**
	 * Returns an instance of a custom property item class that should be used for the property specified.
	 *
	 * @param	InProperty	the property that will use the custom property item
	 * @param	ArrayIndex	specifies which element of an array property that this property window will represent.  Only valid
	 *						when creating property window items for individual elements of an array.
	 * @param	ParentItem	specified the property window item that will contain this new property window item.  Only
	 *						valid when creating property window items for individual array elements or struct member properties
	 *
	 * @return	a pointer to a child of WxItemPropertyControl that should be used as the property
	 *			item for the specified property, or NULL if there is no custom property item configured
	 * 			for the property.
	 */
	class WxItemPropertyControl* GetCustomPropertyWindow( class UProperty* InProperty, INT ArrayIndex=INDEX_NONE);
};

#undef DECLARE_CLASS
#undef DECLARE_CASTED_CLASS
#undef DECLARE_ABSTRACT_CLASS
#undef DECLARE_ABSTRACT_CASTED_CLASS
#endif // !INCLUDED_UNREALED_PRIVATE_CLASSES
#endif // !NAMES_ONLY


#ifndef NAMES_ONLY
#undef AUTOGENERATE_FUNCTION
#endif

#ifdef STATIC_LINKING_MOJO
#ifndef UNREALED_PRIVATE_NATIVE_DEFS
#define UNREALED_PRIVATE_NATIVE_DEFS

#define AUTO_INITIALIZE_REGISTRANTS_UNREALED_PRIVATE \
	UCustomPropertyItemBindings::StaticClass(); \

#endif // UNREALED_PRIVATE_NATIVE_DEFS

#ifdef NATIVES_ONLY
#endif // NATIVES_ONLY
#endif // STATIC_LINKING_MOJO

#ifdef VERIFY_CLASS_SIZES
VERIFY_CLASS_OFFSET_NODIE(UCustomPropertyItemBindings,CustomPropertyItemBindings,CustomPropertyClasses)
VERIFY_CLASS_OFFSET_NODIE(UCustomPropertyItemBindings,CustomPropertyItemBindings,CustomPropertyTypeInputProxies)
VERIFY_CLASS_SIZE_NODIE(UCustomPropertyItemBindings)
#endif // VERIFY_CLASS_SIZES
#endif // !ENUMS_ONLY

#if SUPPORTS_PRAGMA_PACK
#pragma pack (pop)
#endif
