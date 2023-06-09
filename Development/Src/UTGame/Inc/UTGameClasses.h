/*===========================================================================
    C++ class definitions exported from UnrealScript.
    This is automatically generated by the tools.
    DO NOT modify this manually! Edit the corresponding .uc files instead!
    Copyright 1998-2011 Epic Games, Inc. All Rights Reserved.
===========================================================================*/
#if SUPPORTS_PRAGMA_PACK
#pragma pack (push,4)
#endif

#include "UTGameNames.h"

// Split enums from the rest of the header so they can be included earlier
// than the rest of the header file by including this file twice with different
// #define wrappers. See Engine.h and look at EngineClasses.h for an example.
#if !NO_ENUMS && !defined(NAMES_ONLY)

#ifndef INCLUDED_UTGAME_ENUMS
#define INCLUDED_UTGAME_ENUMS 1

enum EVoiceChannel
{
    VC_Spectators           =0,
    VC_Team1                =1,
    VC_Team2                =2,
    VC_MAX                  =3,
};
#define FOREACH_ENUM_EVOICECHANNEL(op) \
    op(VC_Spectators) \
    op(VC_Team1) \
    op(VC_Team2) 
enum EWeapAnimType
{
    EWAT_Default            =0,
    EWAT_Pistol             =1,
    EWAT_DualPistols        =2,
    EWAT_ShoulderRocket     =3,
    EWAT_Stinger            =4,
    EWAT_MAX                =5,
};
#define FOREACH_ENUM_EWEAPANIMTYPE(op) \
    op(EWAT_Default) \
    op(EWAT_Pistol) \
    op(EWAT_DualPistols) \
    op(EWAT_ShoulderRocket) \
    op(EWAT_Stinger) 
enum AmmoWidgetDisplayStyle
{
    EAWDS_Numeric           =0,
    EAWDS_BarGraph          =1,
    EAWDS_Both              =2,
    EAWDS_None              =3,
    EAWDS_MAX               =4,
};
#define FOREACH_ENUM_AMMOWIDGETDISPLAYSTYLE(op) \
    op(EAWDS_Numeric) \
    op(EAWDS_BarGraph) \
    op(EAWDS_Both) \
    op(EAWDS_None) 
enum EZoomState
{
    ZST_NotZoomed           =0,
    ZST_ZoomingOut          =1,
    ZST_ZoomingIn           =2,
    ZST_Zoomed              =3,
    ZST_MAX                 =4,
};
#define FOREACH_ENUM_EZOOMSTATE(op) \
    op(ZST_NotZoomed) \
    op(ZST_ZoomingOut) \
    op(ZST_ZoomingIn) \
    op(ZST_Zoomed) 

#endif // !INCLUDED_UTGAME_ENUMS
#endif // !NO_ENUMS

#if !ENUMS_ONLY

#ifndef NAMES_ONLY
#define AUTOGENERATE_FUNCTION(cls,idx,name)
#endif


#ifndef NAMES_ONLY

#ifndef INCLUDED_UTGAME_CLASSES
#define INCLUDED_UTGAME_CLASSES 1
#define ENABLE_DECLARECLASS_MACRO 1
#include "UnObjBas.h"
#undef ENABLE_DECLARECLASS_MACRO

struct FGameMapCycle
{
    FName GameClassName;
    TArrayNoInit<FString> Maps;

    /** Constructors */
    FGameMapCycle() {}
    FGameMapCycle(EEventParm)
    {
        appMemzero(this, sizeof(FGameMapCycle));
    }
};

struct FActiveBotInfo
{
    FStringNoInit BotName;
    BITFIELD bInUse:1;
    SCRIPT_ALIGN;

    /** Constructors */
    FActiveBotInfo() {}
    FActiveBotInfo(EEventParm)
    {
        appMemzero(this, sizeof(FActiveBotInfo));
    }
};

class AUTGame : public AUDKGame
{
public:
    //## BEGIN PROPS UTGame
    BITFIELD bExportMenuData:1;
    BITFIELD bWeaponStay:1;
    BITFIELD bTeamScoreRounds:1;
    BITFIELD bSoaking:1;
    BITFIELD bPlayersVsBots:1;
    BITFIELD bCustomBots:1;
    BITFIELD bAutoNumBots:1;
    BITFIELD bPlayersMustBeReady:1;
    BITFIELD bForceRespawn:1;
    BITFIELD bTempForceRespawn:1;
    BITFIELD bWaitForNetPlayers:1;
    BITFIELD bShouldWaitForNetPlayers:1;
    BITFIELD bWarmupRound:1;
    BITFIELD bFirstBlood:1;
    BITFIELD bQuickStart:1;
    BITFIELD bSkipPlaySound:1;
    BITFIELD bStartedCountDown:1;
    BITFIELD bFinalStartup:1;
    BITFIELD bOverTimeBroadcast:1;
    BITFIELD bMustHaveMultiplePlayers:1;
    BITFIELD bPlayerBecameActive:1;
    BITFIELD bMustJoinBeforeStart:1;
    BITFIELD bDemoMode:1;
    BITFIELD bUndrivenVehicleDamage:1;
    BITFIELD bStartWithLockerWeaps:1;
    BITFIELD bAllowHoverboard:1;
    BITFIELD bConsoleServer:1;
    BITFIELD bAllowKeyboardAndMouse:1;
    BITFIELD bScoreDeaths:1;
    BITFIELD bPlayedTenKills:1;
    BITFIELD bPlayedFiveKills:1;
    BITFIELD bPlayedOneKill:1;
    BITFIELD bMidGameHasMap:1;
    BITFIELD bForceMidGameMenuAtStart:1;
    BITFIELD bNecrisLocked:1;
    BITFIELD bIgnoreTeamForVoiceChat:1;
    BITFIELD bUseClassicHUD:1;
    BITFIELD bLogGameplayEvents:1;
    BITFIELD bGivePhysicsGun:1;
    FStringNoInit Acronym;
    FStringNoInit Description;
    INT ServerSkillLevel;
    FLOAT EndTimeDelay;
    FLOAT BotRatio;
    INT NetWait;
    INT ClientProcessingTimeout;
    INT MinNetPlayers;
    INT RestartWait;
    INT WarmupTime;
    INT WarmupRemaining;
    BYTE StartupStage;
    BYTE WeaponTauntUsed[20];
    INT DesiredPlayerCount;
    FLOAT SpawnProtectionTime;
    INT DefaultMaxLives;
    INT LateEntryLives;
    INT PendingMatchElapsedTime;
    INT CountDown;
    FLOAT AdjustedDifficulty;
    INT PlayerKills;
    INT PlayerDeaths;
    class ANavigationPoint* LastPlayerStartSpot;
    class ANavigationPoint* LastStartSpot;
    FLOAT EndTime;
    INT EndMessageWait;
    INT EndMessageCounter;
    FStringNoInit RulesMenuType;
    FStringNoInit GameUMenuType;
    class AActor* EndGameFocus;
    INT ResetCountDown;
    INT ResetTimeDelay;
    class AUTVehicle* VehicleList;
    class AUTTeamInfo* EnemyRoster;
    FStringNoInit EnemyRosterName;
    TArrayNoInit<class UClass*> DefaultInventory;
    class UClass* VictoryMessageClass;
    TArrayNoInit<FString> MapPrefixes;
    class UClass* ConsolePlayerControllerClass;
    FStringNoInit DemoPrefix;
    class UClass* BotClass;
    TArrayNoInit<struct FGameMapCycle> GameSpecificMapCycles;
    INT MapCycleIndex;
    TArrayNoInit<struct FActiveBotInfo> ActiveBots;
    class ANavigationPoint* ScriptedStartSpot;
    FStringNoInit EndOfMatchRulesTemplateStr_Scoring;
    FStringNoInit EndOfMatchRulesTemplateStr_ScoringSingle;
    FStringNoInit EndOfMatchRulesTemplateStr_Time;
    class USpeechRecognition* SpeechRecognitionData;
    FLOAT LastEncouragementTime;
    FLOAT LastManDownTime;
    class APawn* Sniper;
    FName MidgameScorePanelTag;
    FStringNoInit GameplayEventsWriterClassName;
    class UGameplayEventsWriter* GameplayEventsWriter;
    TArrayNoInit<FName> SpreeStatEvents;
    //## END PROPS UTGame

    DECLARE_CLASS(AUTGame,AUDKGame,0|CLASS_Config,UTGame)
    NO_DEFAULT_CONSTRUCTOR(AUTGame)
};

#define UCONST_MINTIMEBETWEENPAINSOUNDS 0.35

class AUTPawn : public AUDKPawn
{
public:
    //## BEGIN PROPS UTPawn
    BITFIELD bFixedView:1;
    BITFIELD bSpawnDone:1;
    BITFIELD bSpawnIn:1;
    BITFIELD bShieldAbsorb:1;
    BITFIELD bDodging:1;
    BITFIELD bStopOnDoubleLanding:1;
    BITFIELD bIsInvulnerable:1;
    BITFIELD bJustDroppedOrb:1;
    BITFIELD bForcedFeignDeath:1;
    BITFIELD bWeaponBob:1;
    BITFIELD bJustLanded:1;
    BITFIELD bLandRecovery:1;
    BITFIELD bHasHoverboard:1;
    BITFIELD bStopDeathCamera:1;
    BITFIELD bWinnerCam:1;
    BITFIELD bGibbed:1;
    BITFIELD bHeadGibbed:1;
    BITFIELD bArmsAttached:1;
    BITFIELD bWeaponAttachmentVisible:1;
    BITFIELD bHideOnListenServer:1;
    BITFIELD bPostRenderTraceSucceeded:1;
    BITFIELD bReceivedValidTeam:1;
    BITFIELD bKillsAffectHead:1;
    BITFIELD bKilledByBio:1;
    class UClass* CurrentWeaponAttachmentClass;
    INT UnfeignFailedCount;
    class UDynamicLightEnvironmentComponent* LightEnvironment;
    class UAnimNodeBlend* FeignDeathBlend;
    class UAnimNodeSlot* FullBodyAnimSlot;
    class UAnimNodeSlot* TopHalfAnimSlot;
    FLOAT DeathHipLinSpring;
    FLOAT DeathHipLinDamp;
    FLOAT DeathHipAngSpring;
    FLOAT DeathHipAngDamp;
    FLOAT StartDeathAnimTime;
    class UClass* DeathAnimDamageType;
    FLOAT TimeLastTookDeathAnimDamage;
    FVector FixedViewLoc;
    FRotator FixedViewRot;
    FLOAT CameraScale;
    FLOAT CurrentCameraScale;
    FLOAT CameraScaleMin;
    FLOAT CameraScaleMax;
    FVector OldCameraPosition;
    FLOAT CameraZOffset;
    FLOAT HeroCameraScale;
    INT HeroCameraPitch;
    FLOAT DodgeSpeed;
    FLOAT DodgeSpeedZ;
    BYTE CurrentDir;
    FLOAT DoubleJumpEyeHeight;
    FLOAT DoubleJumpThreshold;
    FLOAT DefaultAirControl;
    FLOAT Bob;
    FLOAT LandBob;
    FLOAT JumpBob;
    FLOAT AppliedBob;
    FLOAT bobtime;
    FVector WalkBob;
    FLOAT FeignDeathBodyAtRestSpeed;
    FLOAT FeignDeathStartTime;
    FLOAT FeignDeathRecoveryStartTime;
    INT SuperHealthMax;
    class UClass* SoundGroupClass;
    class UClass* CurrCharClassInfo;
    TArrayNoInit<FName> TakeHitPhysicsFixedBones;
    TArrayNoInit<FName> NoDriveBodies;
    class UForceFeedbackWaveform* FallingDamageWaveForm;
    FLOAT AccumulateDamage;
    FLOAT AccumulationTime;
    FLOAT LastHoverboardTime;
    FLOAT MinHoverboardInterval;
    class UUTAnimBlendByDriving* DrivingNode;
    class UUTAnimBlendByVehicle* VehicleNode;
    class UUTAnimBlendByHoverboarding* HoverboardingNode;
    FLOAT ShieldBeltArmor;
    FLOAT VestArmor;
    FLOAT ThighpadArmor;
    class AUTWeaponAttachment* CurrentWeaponAttachment;
    FName WeaponSocket;
    FName WeaponSocket2;
    FName PawnEffectSockets[2];
    FLOAT HeadOffset;
    FLOAT HeadRadius;
    FLOAT HeadHeight;
    FName HeadBone;
    class UStaticMeshComponent* HeadshotNeckAttachment;
    class UClass* TransInEffects[2];
    FLinearColor TranslocateColor[2];
    class UCameraAnim* TransCameraAnim[3];
    class USoundCue* ArmorHitSound;
    class USoundCue* SpawnSound;
    class USoundCue* TeleportSound;
    FLinearColor SpawnProtectionColor;
    FLOAT TeamBeaconPlayerInfoMaxDist;
    class UTexture* SpeakingBeaconTexture;
    FLOAT MapSize;
    struct FTextureCoordinates IconCoords;
    FLOAT LastPainSound;
    FLOAT RagdollLifespan;
    class AUTProjectile* AttachedProj;
    FLOAT MaxFootstepDistSq;
    FLOAT MaxJumpSoundDistSq;
    class UClass* HoverboardClass;
    struct FDrivenWeaponPawnInfo LastDrivenWeaponPawn;
    class AUTClientSideWeaponPawn* ClientSideWeaponPawn;
    class UMaterialInterface* ShieldBeltMaterialInstance;
    class UMaterialInterface* ShieldBeltTeamMaterialInstances[4];
    INT JumpBootCharge;
    FLOAT DefaultMeshScale;
    FName TauntNames[6];
    FLOAT DesiredMeshScale;
    FVector CamOffset;
    class UParticleSystemComponent* BioBurnAway;
    FLOAT BioBurnAwayTime;
    FName BioEffectName;
    FLOAT DeathTime;
    //## END PROPS UTPawn

    DECLARE_CLASS(AUTPawn,AUDKPawn,0|CLASS_Config,UTGame)
    NO_DEFAULT_CONSTRUCTOR(AUTPawn)
};

struct UTWeapon_eventGetPowerPerc_Parms
{
    FLOAT ReturnValue;
    UTWeapon_eventGetPowerPerc_Parms(EEventParm)
    {
    }
};
struct UTWeapon_eventStopMuzzleFlash_Parms
{
    UTWeapon_eventStopMuzzleFlash_Parms(EEventParm)
    {
    }
};
struct UTWeapon_eventCauseMuzzleFlash_Parms
{
    UTWeapon_eventCauseMuzzleFlash_Parms(EEventParm)
    {
    }
};
struct UTWeapon_eventCauseMuzzleFlashLight_Parms
{
    UTWeapon_eventCauseMuzzleFlashLight_Parms(EEventParm)
    {
    }
};
struct UTWeapon_eventMuzzleFlashTimer_Parms
{
    UTWeapon_eventMuzzleFlashTimer_Parms(EEventParm)
    {
    }
};
class AUTWeapon : public AUDKWeapon
{
public:
    //## BEGIN PROPS UTWeapon
    BITFIELD bExportMenuData:1;
    BITFIELD bWasLocked:1;
    BITFIELD bUseCustomCoordinates:1;
    BITFIELD bSmallWeapons:1;
    BITFIELD bSuperWeapon:1;
    BITFIELD bNeverForwardPendingFire:1;
    BITFIELD bSuppressSounds:1;
    BITFIELD bUsesOffhand:1;
    BITFIELD bPendingShow:1;
    BITFIELD bShowAltMuzzlePSCWhenWeaponHidden:1;
    BITFIELD bMuzzleFlashPSCLoops:1;
    BITFIELD bMuzzleFlashAttached:1;
    BITFIELD bSplashJump:1;
    BITFIELD bRecommendSplashDamage:1;
    BITFIELD bSniping:1;
    BITFIELD bFastRepeater:1;
    BITFIELD bLockedAimWhileFiring:1;
    BITFIELD bUsingAimingHelp:1;
    BITFIELD bAllowFiringWithoutController:1;
    BITFIELD bTargetFrictionEnabled:1;
    BITFIELD bTargetAdhesionEnabled:1;
    BITFIELD bForceHidden:1;
    BITFIELD bHasLocationSpeech:1;
    class UClass* AmmoPickupClass;
    INT LockerAmmoCount;
    INT MaxAmmoCount;
    TArrayNoInit<INT> ShotCost;
    TArrayNoInit<FLOAT> MinReloadPct;
    TArrayNoInit<class UCameraAnim*> FireCameraAnim;
    class UForceFeedbackWaveform* WeaponFireWaveForm;
    TArrayNoInit<FName> EffectSockets;
    INT IconX;
    INT IconY;
    INT IconWidth;
    INT IconHeight;
    FLOAT SwitchAbortTime;
    struct FTextureCoordinates IconCoordinates;
    struct FTextureCoordinates CrossHairCoordinates;
    struct FTextureCoordinates SimpleCrossHairCoordinates;
    class UTexture2D* CrosshairImage;
    struct FTextureCoordinates LockedCrossHairCoordinates;
    FLOAT CurrentLockedScale;
    FLOAT StartLockedScale;
    FLOAT FinalLockedScale;
    FLOAT LockedScaleTime;
    FLOAT LockedStartTime;
    FLOAT LastHitEnemyTime;
    FColor CrosshairColor;
    FLOAT CrosshairScaling;
    struct FTextureCoordinates CustomCrosshairCoordinates;
    FLOAT DroppedPickupOffsetZ;
    TArrayNoInit<BYTE> bZoomedFireMode;
    BYTE ZoomedFireModeNum;
    BYTE InventoryGroup;
    BYTE AmmoDisplayType;
    FLOAT ZoomedTargetFOV;
    FLOAT ZoomedRate;
    FLOAT ZoomFadeTime;
    class USoundCue* ZoomInSound;
    class USoundCue* ZoomOutSound;
    class UClass* AttachmentClass;
    FVector PivotTranslation;
    FLOAT GroupWeight;
    FLOAT InventoryWeight;
    TArrayNoInit<FName> WeaponFireAnim;
    TArrayNoInit<FName> ArmFireAnim;
    class UAnimSet* ArmsAnimSet;
    FName WeaponPutDownAnim;
    FName ArmsPutDownAnim;
    FName WeaponEquipAnim;
    FName ArmsEquipAnim;
    TArrayNoInit<FName> WeaponIdleAnims;
    TArrayNoInit<FName> ArmIdleAnims;
    TArrayNoInit<class USoundCue*> WeaponFireSnd;
    class USoundCue* WeaponPutDownSnd;
    class USoundCue* WeaponEquipSnd;
    FLOAT BobDamping;
    FLOAT JumpDamping;
    FLOAT MaxPitchLag;
    FLOAT MaxYawLag;
    FLOAT LastRotUpdate;
    FRotator LastRotation;
    FLOAT OldLeadMag[2];
    INT OldRotDiff[2];
    FLOAT OldMaxDiff[2];
    FLOAT RotChgSpeed;
    FLOAT ReturnChgSpeed;
    FColor WeaponColor;
    FLOAT WeaponCanvasXPct;
    FLOAT WeaponCanvasYPct;
    FName MuzzleFlashSocket;
    class UUTParticleSystemComponent* MuzzleFlashPSC;
    class UParticleSystem* MuzzleFlashPSCTemplate;
    class UParticleSystem* MuzzleFlashAltPSCTemplate;
    FColor MuzzleFlashColor;
    class UUDKExplosionLight* MuzzleFlashLight;
    class UClass* MuzzleFlashLightClass;
    FLOAT MuzzleFlashDuration;
    FVector PlayerViewOffset;
    FVector SmallWeaponsOffset;
    FLOAT WideScreenOffsetScaling;
    FRotator WidescreenRotationOffset;
    FVector HiddenWeaponsOffset;
    FLOAT ProjectileSpawnOffset;
    FRotator LockerRotation;
    FVector LockerOffset;
    FLOAT CurrentRating;
    FLOAT aimerror;
    struct FObjectiveAnnouncementInfo NeedToPickUpAnnouncement;
    FLOAT AimingHelpRadius[2];
    FLOAT ZoomedTurnSpeedScalePct;
    FLOAT TargetFrictionDistanceMin;
    FLOAT TargetFrictionDistancePeak;
    FLOAT TargetFrictionDistanceMax;
    FInterpCurveFloat TargetFrictionDistanceCurve;
    FVector2D TargetFrictionMultiplierRange;
    FLOAT TargetFrictionPeakRadiusScale;
    FLOAT TargetFrictionPeakHeightScale;
    FVector TargetFrictionOffset;
    FLOAT TargetFrictionZoomedBoostValue;
    FLOAT TargetAdhesionTimeMax;
    FLOAT TargetAdhesionDistanceMax;
    FLOAT TargetAdhesionAimDistY;
    FLOAT TargetAdhesionAimDistZ;
    FVector2D TargetAdhesionScaleRange;
    FLOAT TargetAdhesionScaleAmountMin;
    FLOAT TargetAdhesionTargetVelocityMin;
    FLOAT TargetAdhesionPlayerVelocityMin;
    FLOAT TargetAdhesionZoomedBoostValue;
    TArrayNoInit<class USoundNodeWave*> LocationSpeech;
    FStringNoInit UseHintString;
    //## END PROPS UTWeapon

    FLOAT eventGetPowerPerc()
    {
        UTWeapon_eventGetPowerPerc_Parms Parms(EC_EventParm);
        Parms.ReturnValue=0;
        ProcessEvent(FindFunctionChecked(UTGAME_GetPowerPerc),&Parms);
        return Parms.ReturnValue;
    }
    void eventStopMuzzleFlash()
    {
        ProcessEvent(FindFunctionChecked(UTGAME_StopMuzzleFlash),NULL);
    }
    void eventCauseMuzzleFlash()
    {
        ProcessEvent(FindFunctionChecked(UTGAME_CauseMuzzleFlash),NULL);
    }
    void eventCauseMuzzleFlashLight()
    {
        ProcessEvent(FindFunctionChecked(UTGAME_CauseMuzzleFlashLight),NULL);
    }
    void eventMuzzleFlashTimer()
    {
        ProcessEvent(FindFunctionChecked(UTGAME_MuzzleFlashTimer),NULL);
    }
    DECLARE_ABSTRACT_CLASS(AUTWeapon,AUDKWeapon,0|CLASS_Config,UTGame)
    static const TCHAR* StaticConfigName() {return TEXT("Weapon");}

    NO_DEFAULT_CONSTRUCTOR(AUTWeapon)
};

#undef DECLARE_CLASS
#undef DECLARE_CASTED_CLASS
#undef DECLARE_ABSTRACT_CLASS
#undef DECLARE_ABSTRACT_CASTED_CLASS
#endif // !INCLUDED_UTGAME_CLASSES
#endif // !NAMES_ONLY


#ifndef NAMES_ONLY
#undef AUTOGENERATE_FUNCTION
#endif

#ifdef STATIC_LINKING_MOJO
#ifndef UTGAME_NATIVE_DEFS
#define UTGAME_NATIVE_DEFS

#define AUTO_INITIALIZE_REGISTRANTS_UTGAME \
	AUTGame::StaticClass(); \
	AUTPawn::StaticClass(); \
	AUTWeapon::StaticClass(); \

#endif // UTGAME_NATIVE_DEFS

#ifdef NATIVES_ONLY
#endif // NATIVES_ONLY
#endif // STATIC_LINKING_MOJO

#ifdef VERIFY_CLASS_SIZES
VERIFY_CLASS_OFFSET_NODIE(AUTGame,UTGame,Acronym)
VERIFY_CLASS_OFFSET_NODIE(AUTGame,UTGame,SpreeStatEvents)
VERIFY_CLASS_SIZE_NODIE(AUTGame)
VERIFY_CLASS_OFFSET_NODIE(AUTPawn,UTPawn,CurrentWeaponAttachmentClass)
VERIFY_CLASS_OFFSET_NODIE(AUTPawn,UTPawn,DeathTime)
VERIFY_CLASS_SIZE_NODIE(AUTPawn)
VERIFY_CLASS_OFFSET_NODIE(AUTWeapon,UTWeapon,AmmoPickupClass)
VERIFY_CLASS_OFFSET_NODIE(AUTWeapon,UTWeapon,UseHintString)
VERIFY_CLASS_SIZE_NODIE(AUTWeapon)
#endif // VERIFY_CLASS_SIZES
#endif // !ENUMS_ONLY

#if SUPPORTS_PRAGMA_PACK
#pragma pack (pop)
#endif
