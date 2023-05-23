// UTGAME.cpp
//

#include "UTGame.h"

/*-----------------------------------------------------------------------------
	The following must be done once per package.
-----------------------------------------------------------------------------*/

#define STATIC_LINKING_MOJO 1

// Register things.
#define NAMES_ONLY
#define AUTOGENERATE_NAME(name) FName UTGAME_##name;
#define AUTOGENERATE_FUNCTION(cls,idx,name) IMPLEMENT_FUNCTION(cls,idx,name)
#include "UTGameClasses.h"
#undef AUTOGENERATE_NAME

#undef AUTOGENERATE_FUNCTION
#undef NAMES_ONLY

// Register natives.
#define NATIVES_ONLY
#define NAMES_ONLY
#define AUTOGENERATE_NAME(name)
#define AUTOGENERATE_FUNCTION(cls,idx,name)
#include "UTGameClasses.h"
#undef AUTOGENERATE_NAME

#undef AUTOGENERATE_FUNCTION
#undef NATIVES_ONLY
#undef NAMES_ONLY

#if CHECK_NATIVE_CLASS_SIZES
#if _MSC_VER
#pragma optimize( "", off )
#endif

void AutoCheckNativeClassSizesUTGAME( UBOOL& Mismatch )
{
#define NAMES_ONLY
#define AUTOGENERATE_NAME( name )
#define AUTOGENERATE_FUNCTION( cls, idx, name )
#define VERIFY_CLASS_SIZES
#include "UTGAMEClasses.h"
#undef AUTOGENERATE_FUNCTION
#undef AUTOGENERATE_NAME
#undef NAMES_ONLY
#undef VERIFY_CLASS_SIZES
}

#if _MSC_VER
#pragma optimize( "", on )
#endif
#endif

/**
 * Initialize registrants, basically calling StaticClass() to create the class and also
 * populating the lookup table.
 *
 * @param	Lookup	current index into lookup table
 */
void AutoInitializeRegistrantsUTGame( INT& Lookup )
{
	AUTO_INITIALIZE_REGISTRANTS_UTGAME;
}

/**
 * Auto generates names.
 */
void AutoGenerateNamesUTGame()
{
	#define NAMES_ONLY
    #define AUTOGENERATE_NAME(name) UTGAME_##name = FName(TEXT(#name));
//		#include "UTGAMENames.h"
	#undef AUTOGENERATE_NAME

	#define AUTOGENERATE_FUNCTION(cls,idx,name)
	#include "UTGameClasses.h"
	#undef AUTOGENERATE_FUNCTION
	#undef NAMES_ONLY
}

IMPLEMENT_CLASS(AUTPawn)
IMPLEMENT_CLASS(AUTWeapon)
IMPLEMENT_CLASS(AUTGame)