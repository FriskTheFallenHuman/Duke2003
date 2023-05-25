/*===========================================================================
    C++ class definitions exported from UnrealScript.
    This is automatically generated by the tools.
    DO NOT modify this manually! Edit the corresponding .uc files instead!
    Copyright 1998-2011 Epic Games, Inc. All Rights Reserved.
===========================================================================*/
#if SUPPORTS_PRAGMA_PACK
#pragma pack (push,4)
#endif

#include "dnGameNames.h"

// Split enums from the rest of the header so they can be included earlier
// than the rest of the header file by including this file twice with different
// #define wrappers. See Engine.h and look at EngineClasses.h for an example.
#if !NO_ENUMS && !defined(NAMES_ONLY)

#ifndef INCLUDED_DNGAME_ENUMS
#define INCLUDED_DNGAME_ENUMS 1

enum EIntelligence
{
    BRAINS_NONE             =0,
    BRAINS_REPTILE          =1,
    BRAINS_MAMMAL           =2,
    BRAINS_HUMAN            =3,
    BRAINS_MAX              =4,
};
#define FOREACH_ENUM_EINTELLIGENCE(op) \
    op(BRAINS_NONE) \
    op(BRAINS_REPTILE) \
    op(BRAINS_MAMMAL) \
    op(BRAINS_HUMAN) 
enum EAttitude
{
    ATTITUDE_Fear           =0,
    ATTITUDE_Hate           =1,
    ATTITUDE_Frenzy         =2,
    ATTITUDE_Threaten       =3,
    ATTITUDE_Ignore         =4,
    ATTITUDE_Friendly       =5,
    ATTITUDE_Follow         =6,
    ATTITUDE_MAX            =7,
};
#define FOREACH_ENUM_EATTITUDE(op) \
    op(ATTITUDE_Fear) \
    op(ATTITUDE_Hate) \
    op(ATTITUDE_Frenzy) \
    op(ATTITUDE_Threaten) \
    op(ATTITUDE_Ignore) \
    op(ATTITUDE_Friendly) \
    op(ATTITUDE_Follow) 

#endif // !INCLUDED_DNGAME_ENUMS
#endif // !NO_ENUMS

#if !ENUMS_ONLY

#ifndef NAMES_ONLY
#define AUTOGENERATE_FUNCTION(cls,idx,name)
#endif


#ifndef NAMES_ONLY

#ifndef INCLUDED_DNGAME_CLASSES
#define INCLUDED_DNGAME_CLASSES 1
#define ENABLE_DECLARECLASS_MACRO 1
#include "UnObjBas.h"
#undef ENABLE_DECLARECLASS_MACRO

struct FSNPCAnimEvent
{
    BITFIELD bEnabled:1;
    FName TriggerEvent;
    FLOAT SoundVolume;

    /** Constructors */
    FSNPCAnimEvent() {}
    FSNPCAnimEvent(EEventParm)
    {
        appMemzero(this, sizeof(FSNPCAnimEvent));
    }
};

struct AIPawn_eventSeeFocalPoint_Parms
{
    class AActor* PointSeen;
    AIPawn_eventSeeFocalPoint_Parms(EEventParm)
    {
    }
};
class AAIPawn : public APawn
{
public:
    //## BEGIN PROPS AIPawn
    FLOAT Skill;
    BITFIELD bSnatched:1;
    BITFIELD bFixedEnemy:1;
    BITFIELD bRotateToEnemy:1;
    BITFIELD bFromWall:1;
    BITFIELD bHunting:1;
    BITFIELD bJumpOffPawn:1;
    BITFIELD bShootSpecial:1;
    BITFIELD bAdvancedTactics:1;
    BITFIELD bPlayerCanSeeMe:1;
    BITFIELD bMuffledHearing:1;
    BITFIELD bNoHeightMod:1;
    BITFIELD bNoRotConstraint:1;
    BITFIELD bCanStrafe:1;
    BITFIELD bCanJump:1;
    BITFIELD bCanWalk:1;
    BITFIELD bCanSwim:1;
    BITFIELD bCanFly:1;
    BITFIELD bCanOpenDoors:1;
    BITFIELD bCanDoSpecial:1;
    BITFIELD bPanicking:1;
    BITFIELD bWeaponNoAnimSound:1;
    BITFIELD bFlyingVehicle:1;
    BITFIELD bAlwaysUseTentacles:1;
    BITFIELD bCanHaveCash:1;
    BITFIELD bAggressiveToPlayer:1;
    BITFIELD bVisiblySnatched:1;
    BITFIELD bPatrolled:1;
    BITFIELD bFollowEventOnceOnly:1;
    BITFIELD bHateWhenSnatched:1;
    BITFIELD bFire:1;
    BITFIELD bForcedAttack:1;
    BITFIELD bShielded:1;
    BITFIELD bCamping:1;
    BITFIELD bFocusOnPlayer:1;
    BITFIELD bCanBeUsed:1;
    BITFIELD bDisableUseTrigEvent:1;
    BITFIELD bFollowEventDisabled:1;
    BITFIELD bSnatchedAtStartup:1;
    BITFIELD bSleeping:1;
    BITFIELD bEyeless:1;
    BITFIELD bLegless:1;
    BITFIELD bCanHeadTrack:1;
    BITFIELD bCanTorsoTrack:1;
    BITFIELD bReadyToAttack:1;
    BITFIELD bSawEnemy:1;
    BITFIELD bEMPed:1;
    class AActor* Enemy;
    FLOAT MeleeRange;
    FVector LastSeenPos;
    FVector LastSeeingPos;
    FLOAT LastSeenTime;
    FLOAT CombatStyle;
    FLOAT Alertness;
    FName NextState;
    FName NextLabel;
    FLOAT HearThroughWallDist;
    BYTE AttitudeToPlayer;
    BYTE Intelligence;
    BYTE Visibility;
    FLOAT HearingThreshold;
    FVector noise1spot;
    FLOAT noise1time;
    FLOAT noise1loudness;
    FVector noise2spot;
    FLOAT noise2time;
    FLOAT noise2loudness;
    FLOAT SightRadius;
    FLOAT PeripheralVision;
    FLOAT SightCounter;
    INT EgoKillValue;
    FStringNoInit CharacterName;
    FName InitialIdlingAnim;
    FName InitialTopIdlingAnim;
    FLOAT RunSpeed;
    FName HateTag;
    FLOAT AggroSnatchDistance;
    FName PatrolTag;
    FName FollowEvent;
    FLOAT AIMeleeRange;
    FName ControlTag;
    FName CoverTag;
    FName PendingTopAnimation;
    FName PendingBottomAnimation;
    FName PendingAllAnimation;
    FName PendingFocusTag;
    class AActor* MyGiveItem;
    class AActor* AEDestination;
    class AActor* PendingTriggerActor;
    class AActor* Obstruction;
    FLOAT WalkingSpeed;
    class AActor* PendingDoor;
    class AActor* OrderObject;
    struct FSNPCAnimEvent NPCAnimEvent[15];
    class AActor* SuspiciousActor;
    FVector WanderDir;
    //## END PROPS AIPawn

    void eventSeeFocalPoint(class AActor* PointSeen)
    {
        AIPawn_eventSeeFocalPoint_Parms Parms(EC_EventParm);
        Parms.PointSeen=PointSeen;
        ProcessEvent(FindFunctionChecked(DNGAME_SeeFocalPoint),&Parms);
    }
    DECLARE_ABSTRACT_CLASS(AAIPawn,APawn,0|CLASS_Config,dnGame)
    NO_DEFAULT_CONSTRUCTOR(AAIPawn)
};

struct Decoration_eventNotReachableBy_Parms
{
    class APawn* P;
    Decoration_eventNotReachableBy_Parms(EEventParm)
    {
    }
};
class ADecoration : public APawn
{
public:
    //## BEGIN PROPS Decoration
    class UClass* EffectWhenDestroyed;
    BITFIELD bPushable:1;
    BITFIELD bDamageable:1;
    BITFIELD bPushSoundPlaying:1;
    BITFIELD bSplash:1;
    class USoundCue* PushSound;
    class USoundCue* EndPushSound;
    INT numLandings;
    class UClass* contents;
    INT NumFrags;
    class UTexture* FragSkin;
    FVector FragMomentum;
    INT Health;
    FLOAT SplashTime;
    FLOAT LastValidAnchorTime;
    //## END PROPS Decoration

    void eventNotReachableBy(class APawn* P)
    {
        Decoration_eventNotReachableBy_Parms Parms(EC_EventParm);
        Parms.P=P;
        ProcessEvent(FindFunctionChecked(DNGAME_NotReachableBy),&Parms);
    }
    DECLARE_ABSTRACT_CLASS(ADecoration,APawn,0|CLASS_Config,dnGame)
    NO_DEFAULT_CONSTRUCTOR(ADecoration)
};

class AdnSinglePlayer : public AUTGame
{
public:
    //## BEGIN PROPS dnSinglePlayer
    //## END PROPS dnSinglePlayer

    DECLARE_CLASS(AdnSinglePlayer,AUTGame,0|CLASS_Config,dnGame)
    NO_DEFAULT_CONSTRUCTOR(AdnSinglePlayer)
};

class AdnWeapon : public AUTWeapon
{
public:
    //## BEGIN PROPS dnWeapon
    //## END PROPS dnWeapon

    DECLARE_ABSTRACT_CLASS(AdnWeapon,AUTWeapon,0|CLASS_Config,dnGame)
	UBOOL Tick( FLOAT DeltaSeconds, ELevelTick TickType );
};

class APistol : public AdnWeapon
{
public:
    //## BEGIN PROPS Pistol
    //## END PROPS Pistol

    DECLARE_CLASS(APistol,AdnWeapon,0|CLASS_Config,dnGame)
    NO_DEFAULT_CONSTRUCTOR(APistol)
};

class ADukeHUD : public AHUD
{
public:
    //## BEGIN PROPS DukeHUD
    FLOAT Opacity;
    FColor CrosshairColor;
    FColor TextColor;
    FColor HUDColor;
    INT CrosshairCount;
    class UTexture* CrosshairTextures[20];
    FLOAT DesiredIndexTop;
    FLOAT RootIndexTop;
    FLOAT IndexTop;
    FLOAT IndexBottom;
    FLOAT IndexAdjust;
    FLOAT BarOffset;
    FLOAT HUDScale;
    FLOAT HUDScaleX;
    FLOAT HUDScaleY;
    INT MaxIndexItems;
    INT ItemSpace;
    FLOAT TextRightAdjust;
    FLOAT BarPos;
    FLOAT BarLeft;
    FLOAT TitleLeft;
    FLOAT TitleOffset;
    FLOAT SlideRate;
    FLOAT IndexTopOffset;
    FStringNoInit IndexName;
    class UTexture* GradientTexture;
    class UTexture* IndexBarLeftTexture;
    class UTexture* IndexBarRightTexture;
    class UTexture* IndexBarBottomTexture;
    class UTexture* InventoryBarTopTexture;
    class UTexture* InventoryBarBotTexture;
    class UTexture* InventoryCatHLTexture;
    class UTexture* InventoryCatHLTexture2;
    class UTexture* MiscBarTabTexture;
    class UTexture* MiscBarHLTexture;
    class UTexture* HUDTemplateTexture;
    class UTexture* ItemSlantTexture;
    class UTexture* ItemSlantHLTexture;
    class UTexture* MiscBarTexture;
    class UTexture* MiscBarTexture2;
    class UTexture* NumberCircleTexture;
    //## END PROPS DukeHUD

    virtual void HudStartup();
    virtual void RenderHud();
    virtual void DrawScaledTexture(class UTexture* Icon,FLOAT X,FLOAT Y,FVector Scale);
    DECLARE_FUNCTION(execHudStartup)
    {
        P_FINISH;
        this->HudStartup();
    }
    DECLARE_FUNCTION(execRenderHud)
    {
        P_FINISH;
        this->RenderHud();
    }
    DECLARE_FUNCTION(execDrawScaledTexture)
    {
        P_GET_OBJECT(UTexture,Icon);
        P_GET_FLOAT(X);
        P_GET_FLOAT(Y);
        P_GET_STRUCT(FVector,Scale);
        P_FINISH;
        this->DrawScaledTexture(Icon,X,Y,Scale);
    }
    DECLARE_CLASS(ADukeHUD,AHUD,0|CLASS_Transient|CLASS_Config,dnGame)
	void DrawStatusIndex();
	void DrawCrosshair();
};

class APlayerPawn : public AUTPawn
{
public:
    //## BEGIN PROPS PlayerPawn
    //## END PROPS PlayerPawn

    DECLARE_CLASS(APlayerPawn,AUTPawn,0|CLASS_Config|CLASS_NativeReplication,dnGame)
    NO_DEFAULT_CONSTRUCTOR(APlayerPawn)
};

#undef DECLARE_CLASS
#undef DECLARE_CASTED_CLASS
#undef DECLARE_ABSTRACT_CLASS
#undef DECLARE_ABSTRACT_CASTED_CLASS
#endif // !INCLUDED_DNGAME_CLASSES
#endif // !NAMES_ONLY

AUTOGENERATE_FUNCTION(ADukeHUD,-1,execDrawScaledTexture);
AUTOGENERATE_FUNCTION(ADukeHUD,-1,execRenderHud);
AUTOGENERATE_FUNCTION(ADukeHUD,-1,execHudStartup);

#ifndef NAMES_ONLY
#undef AUTOGENERATE_FUNCTION
#endif

#ifdef STATIC_LINKING_MOJO
#ifndef DNGAME_NATIVE_DEFS
#define DNGAME_NATIVE_DEFS

#define AUTO_INITIALIZE_REGISTRANTS_DNGAME \
	AAIPawn::StaticClass(); \
	ADecoration::StaticClass(); \
	AdnSinglePlayer::StaticClass(); \
	AdnWeapon::StaticClass(); \
	APistol::StaticClass(); \
	ADukeHUD::StaticClass(); \
	GNativeLookupFuncs.Set(FName("DukeHUD"), GdnGameADukeHUDNatives); \
	APlayerPawn::StaticClass(); \

#endif // DNGAME_NATIVE_DEFS

#ifdef NATIVES_ONLY
FNativeFunctionLookup GdnGameADukeHUDNatives[] = 
{ 
	MAP_NATIVE(ADukeHUD, execDrawScaledTexture)
	MAP_NATIVE(ADukeHUD, execRenderHud)
	MAP_NATIVE(ADukeHUD, execHudStartup)
	{NULL, NULL}
};

#endif // NATIVES_ONLY
#endif // STATIC_LINKING_MOJO

#ifdef VERIFY_CLASS_SIZES
VERIFY_CLASS_OFFSET_NODIE(AAIPawn,AIPawn,Skill)
VERIFY_CLASS_OFFSET_NODIE(AAIPawn,AIPawn,WanderDir)
VERIFY_CLASS_SIZE_NODIE(AAIPawn)
VERIFY_CLASS_OFFSET_NODIE(ADecoration,Decoration,EffectWhenDestroyed)
VERIFY_CLASS_OFFSET_NODIE(ADecoration,Decoration,LastValidAnchorTime)
VERIFY_CLASS_SIZE_NODIE(ADecoration)
VERIFY_CLASS_SIZE_NODIE(AdnSinglePlayer)
VERIFY_CLASS_SIZE_NODIE(AdnWeapon)
VERIFY_CLASS_SIZE_NODIE(APistol)
VERIFY_CLASS_OFFSET_NODIE(ADukeHUD,DukeHUD,Opacity)
VERIFY_CLASS_OFFSET_NODIE(ADukeHUD,DukeHUD,NumberCircleTexture)
VERIFY_CLASS_SIZE_NODIE(ADukeHUD)
VERIFY_CLASS_SIZE_NODIE(APlayerPawn)
#endif // VERIFY_CLASS_SIZES
#endif // !ENUMS_ONLY

#if SUPPORTS_PRAGMA_PACK
#pragma pack (pop)
#endif
