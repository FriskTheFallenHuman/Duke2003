/*===========================================================================
    C++ class definitions exported from UnrealScript.
    This is automatically generated by the tools.
    DO NOT modify this manually! Edit the corresponding .uc files instead!
    Copyright 1998-2011 Epic Games, Inc. All Rights Reserved.
===========================================================================*/
#if SUPPORTS_PRAGMA_PACK
#pragma pack (push,4)
#endif

#include "EngineNames.h"

// Split enums from the rest of the header so they can be included earlier
// than the rest of the header file by including this file twice with different
// #define wrappers. See Engine.h and look at EngineClasses.h for an example.
#if !NO_ENUMS && !defined(NAMES_ONLY)

#ifndef INCLUDED_ENGINE_AUDIODEVICE_ENUMS
#define INCLUDED_ENGINE_AUDIODEVICE_ENUMS 1

enum ETTSSpeaker
{
    TTSSPEAKER_Paul         =0,
    TTSSPEAKER_Harry        =1,
    TTSSPEAKER_Frank        =2,
    TTSSPEAKER_Dennis       =3,
    TTSSPEAKER_Kit          =4,
    TTSSPEAKER_Betty        =5,
    TTSSPEAKER_Ursula       =6,
    TTSSPEAKER_Rita         =7,
    TTSSPEAKER_Wendy        =8,
    TTSSPEAKER_MAX          =9,
};
#define FOREACH_ENUM_ETTSSPEAKER(op) \
    op(TTSSPEAKER_Paul) \
    op(TTSSPEAKER_Harry) \
    op(TTSSPEAKER_Frank) \
    op(TTSSPEAKER_Dennis) \
    op(TTSSPEAKER_Kit) \
    op(TTSSPEAKER_Betty) \
    op(TTSSPEAKER_Ursula) \
    op(TTSSPEAKER_Rita) \
    op(TTSSPEAKER_Wendy) 
enum EDebugState
{
    DEBUGSTATE_None         =0,
    DEBUGSTATE_IsolateDryAudio=1,
    DEBUGSTATE_IsolateReverb=2,
    DEBUGSTATE_TestLPF      =3,
    DEBUGSTATE_TestStereoBleed=4,
    DEBUGSTATE_TestLFEBleed =5,
    DEBUGSTATE_DisableLPF   =6,
    DEBUGSTATE_DisableRadio =7,
    DEBUGSTATE_MAX          =8,
};
#define FOREACH_ENUM_EDEBUGSTATE(op) \
    op(DEBUGSTATE_None) \
    op(DEBUGSTATE_IsolateDryAudio) \
    op(DEBUGSTATE_IsolateReverb) \
    op(DEBUGSTATE_TestLPF) \
    op(DEBUGSTATE_TestStereoBleed) \
    op(DEBUGSTATE_TestLFEBleed) \
    op(DEBUGSTATE_DisableLPF) \
    op(DEBUGSTATE_DisableRadio) 
enum ESoundClassName
{
    Master                  =0,
    ESoundClassName_MAX     =1,
};
#define FOREACH_ENUM_ESOUNDCLASSNAME(op) \
    op(Master) 

#endif // !INCLUDED_ENGINE_AUDIODEVICE_ENUMS
#endif // !NO_ENUMS

#if !ENUMS_ONLY

#ifndef NAMES_ONLY
#define AUTOGENERATE_FUNCTION(cls,idx,name)
#endif


#ifndef NAMES_ONLY

#ifndef INCLUDED_ENGINE_AUDIODEVICE_CLASSES
#define INCLUDED_ENGINE_AUDIODEVICE_CLASSES 1
#define ENABLE_DECLARECLASS_MACRO 1
#include "UnObjBas.h"
#undef ENABLE_DECLARECLASS_MACRO

struct FSoundClassEditorData
{
    INT NodePosX;
    INT NodePosY;
    friend FArchive& operator<<(FArchive& Ar,FSoundClassEditorData& MySoundClassEditorData)
    {
        return Ar << MySoundClassEditorData.NodePosX << MySoundClassEditorData.NodePosY;
    }

    /** Constructors */
    FSoundClassEditorData() {}
    FSoundClassEditorData(EEventParm)
    {
        appMemzero(this, sizeof(FSoundClassEditorData));
    }
};

struct FSoundClassProperties
{
    FLOAT Volume;
    FLOAT Pitch;
    FLOAT StereoBleed;
    FLOAT LFEBleed;
    FLOAT VoiceCenterChannelVolume;
    FLOAT RadioFilterVolume;
    FLOAT RadioFilterVolumeThreshold;
    BITFIELD bApplyEffects:1;
    BITFIELD bAlwaysPlay:1;
    BITFIELD bIsUISound:1;
    BITFIELD bIsMusic:1;
    BITFIELD bReverb:1;
    BITFIELD bCenterChannelOnly:1;
    SCRIPT_ALIGN;

    /** Constructors */
    FSoundClassProperties() {}
    FSoundClassProperties(EEventParm)
    {
        appMemzero(this, sizeof(FSoundClassProperties));
    }
};

class USoundClass : public UObject
{
public:
    //## BEGIN PROPS SoundClass
    struct FSoundClassProperties Properties;
    TArrayNoInit<FName> ChildClassNames;
    BITFIELD bIsChild:1;
    INT MenuID;
    TMap< USoundClass*, FSoundClassEditorData > EditorData;
    //## END PROPS SoundClass

    DECLARE_CLASS(USoundClass,UObject,0,Engine)
    #include "USoundClass.h"
};

struct FListener
{
    class APortalVolume* PortalVolume;
    FVector Location;
    FVector Up;
    FVector Right;
    FVector Front;

    /** Constructors */
    FListener() {}
    FListener(EEventParm)
    {
        appMemzero(this, sizeof(FListener));
    }
};

struct FAudioClassInfo
{
    INT NumResident;
    INT SizeResident;
    INT NumRealTime;
    INT SizeRealTime;

    /** Constructors */
    FAudioClassInfo() {}
    FAudioClassInfo(EEventParm)
    {
        appMemzero(this, sizeof(FAudioClassInfo));
    }
};

class UAudioDevice : public USubsystem
{
public:
    //## BEGIN PROPS AudioDevice
    INT MaxChannels;
    INT CommonAudioPoolSize;
    FLOAT LowPassFilterResonance;
    BITFIELD WorkAroundXDKRegression:1;
    BITFIELD bGameWasTicking:1;
    FLOAT MinCompressedDurationEditor;
    FLOAT MinCompressedDurationGame;
    FStringNoInit ChirpInSoundNodeWaveName;
    class USoundNodeWave* ChirpInSoundNodeWave;
    FStringNoInit ChirpOutSoundNodeWaveName;
    class USoundNodeWave* ChirpOutSoundNodeWave;
    FPointer CommonAudioPool;
    INT CommonAudioPoolFreeBytes;
    TArrayNoInit<class UAudioComponent*> AudioComponents;
    TArrayNoInit<FSoundSource*> Sources;
    TArrayNoInit<FSoundSource*> FreeSources;
    TMap< FWaveInstance*, FSoundSource* > WaveInstanceSourceMap;
    TArrayNoInit<struct FListener> Listeners;
    QWORD CurrentTick;
    TMap< FName, class USoundClass* > SoundClasses;
    TMap< FName, struct FSoundClassProperties > SourceSoundClasses;
    TMap< FName, struct FSoundClassProperties > CurrentSoundClasses;
    TMap< FName, struct FSoundClassProperties > DestinationSoundClasses;
    TMap< FName, class USoundMode* > SoundModes;
    class FAudioEffectsManager* Effects;
    FName BaseSoundModeName;
    class USoundMode* CurrentMode;
    DOUBLE SoundModeStartTime;
    DOUBLE SoundModeFadeInStartTime;
    DOUBLE SoundModeFadeInEndTime;
    DOUBLE SoundModeEndTime;
    INT ListenerVolumeIndex;
    FInteriorSettings ListenerInteriorSettings;
    DOUBLE InteriorStartTime;
    DOUBLE InteriorEndTime;
    DOUBLE ExteriorEndTime;
    DOUBLE InteriorLPFEndTime;
    DOUBLE ExteriorLPFEndTime;
    FLOAT InteriorVolumeInterp;
    FLOAT InteriorLPFInterp;
    FLOAT ExteriorVolumeInterp;
    FLOAT ExteriorLPFInterp;
    class UAudioComponent* TestAudioComponent;
    class FTextToSpeech* TextToSpeech;
    BYTE DebugState;
    FLOAT TransientMasterVolume;
    FLOAT LastUpdateTime;
    //## END PROPS AudioDevice

    UBOOL SetSoundMode(FName NewMode);
    class USoundClass* FindSoundClass(FName SoundClassName);
    DECLARE_FUNCTION(execSetSoundMode)
    {
        P_GET_NAME(NewMode);
        P_FINISH;
        *(UBOOL*)Result=this->SetSoundMode(NewMode);
    }
    DECLARE_FUNCTION(execFindSoundClass)
    {
        P_GET_NAME(SoundClassName);
        P_FINISH;
        *(class USoundClass**)Result=this->FindSoundClass(SoundClassName);
    }
    DECLARE_CLASS(UAudioDevice,USubsystem,0|CLASS_Transient|CLASS_Config,Engine)
    static const TCHAR* StaticConfigName() {return TEXT("Engine");}

    #include "UAudioDevice.h"
};

struct FAudioEQEffect
{
    DOUBLE RootTime;
    FLOAT HFFrequency;
    FLOAT HFGain;
    FLOAT MFCutoffFrequency;
    FLOAT MFBandwidth;
    FLOAT MFGain;
    FLOAT LFFrequency;
    FLOAT LFGain;

		// Cannot use strcutdefaultproperties here as this class is a member of a native class
		FAudioEQEffect( void ) :
			RootTime( 0.0 ),
			HFFrequency( DEFAULT_HIGH_FREQUENCY ),
			HFGain( 1.0f ),
			MFCutoffFrequency( DEFAULT_MID_FREQUENCY ),
			MFBandwidth( 1.0f ),
			MFGain( 1.0f ),
			LFFrequency( DEFAULT_LOW_FREQUENCY ),
			LFGain( 1.0f )
		{
		}

		/** 
		 * Interpolate EQ settings based on time
		 */
		void Interpolate( FLOAT InterpValue, const FAudioEQEffect& Start, const FAudioEQEffect& End );
		
		/** 
		 * Validate all settings are in range
		 */
		void ClampValues( void );
	
};

struct FSoundClassAdjuster
{
    BYTE SoundClassName;
    FName SoundClass;
    FLOAT VolumeAdjuster;
    FLOAT PitchAdjuster;
    BITFIELD bApplyToChildren:1;
    FLOAT VoiceCenterChannelVolumeAdjuster;

    /** Constructors */
    FSoundClassAdjuster() {}
    FSoundClassAdjuster(EEventParm)
    {
        appMemzero(this, sizeof(FSoundClassAdjuster));
    }
};

class USoundMode : public UObject
{
public:
    //## BEGIN PROPS SoundMode
    BITFIELD bApplyEQ:1;
    SCRIPT_ALIGN;
    struct FAudioEQEffect EQSettings;
    TArrayNoInit<struct FSoundClassAdjuster> SoundClassEffects;
    FLOAT InitialDelay;
    FLOAT FadeInTime;
    FLOAT Duration;
    FLOAT FadeOutTime;
    //## END PROPS SoundMode

    DECLARE_CLASS(USoundMode,UObject,0,Engine)
    #include "USoundMode.h"
};

#undef DECLARE_CLASS
#undef DECLARE_CASTED_CLASS
#undef DECLARE_ABSTRACT_CLASS
#undef DECLARE_ABSTRACT_CASTED_CLASS
#endif // !INCLUDED_ENGINE_AUDIODEVICE_CLASSES
#endif // !NAMES_ONLY

AUTOGENERATE_FUNCTION(UAudioDevice,-1,execFindSoundClass);
AUTOGENERATE_FUNCTION(UAudioDevice,-1,execSetSoundMode);

#ifndef NAMES_ONLY
#undef AUTOGENERATE_FUNCTION
#endif

#ifdef STATIC_LINKING_MOJO
#ifndef ENGINE_AUDIODEVICE_NATIVE_DEFS
#define ENGINE_AUDIODEVICE_NATIVE_DEFS

#define AUTO_INITIALIZE_REGISTRANTS_ENGINE_AUDIODEVICE \
	UAudioDevice::StaticClass(); \
	GNativeLookupFuncs.Set(FName("AudioDevice"), GEngineUAudioDeviceNatives); \
	USoundClass::StaticClass(); \
	USoundMode::StaticClass(); \

#endif // ENGINE_AUDIODEVICE_NATIVE_DEFS

#ifdef NATIVES_ONLY
FNativeFunctionLookup GEngineUAudioDeviceNatives[] = 
{ 
	MAP_NATIVE(UAudioDevice, execFindSoundClass)
	MAP_NATIVE(UAudioDevice, execSetSoundMode)
	{NULL, NULL}
};

#endif // NATIVES_ONLY
#endif // STATIC_LINKING_MOJO

#ifdef VERIFY_CLASS_SIZES
VERIFY_CLASS_OFFSET_NODIE(UAudioDevice,AudioDevice,MaxChannels)
VERIFY_CLASS_OFFSET_NODIE(UAudioDevice,AudioDevice,LastUpdateTime)
VERIFY_CLASS_SIZE_NODIE(UAudioDevice)
VERIFY_CLASS_OFFSET_NODIE(USoundClass,SoundClass,Properties)
VERIFY_CLASS_OFFSET_NODIE(USoundClass,SoundClass,EditorData)
VERIFY_CLASS_SIZE_NODIE(USoundClass)
VERIFY_CLASS_OFFSET_NODIE(USoundMode,SoundMode,EQSettings)
VERIFY_CLASS_OFFSET_NODIE(USoundMode,SoundMode,FadeOutTime)
VERIFY_CLASS_SIZE_NODIE(USoundMode)
#endif // VERIFY_CLASS_SIZES
#endif // !ENUMS_ONLY

#if SUPPORTS_PRAGMA_PACK
#pragma pack (pop)
#endif