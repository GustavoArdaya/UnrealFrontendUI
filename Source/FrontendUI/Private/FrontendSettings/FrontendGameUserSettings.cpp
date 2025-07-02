// Vince Petrelli


#include "FrontendSettings/FrontendGameUserSettings.h"

UFrontendGameUserSettings::UFrontendGameUserSettings()
	: OverallVolume(1.f), MusicVolume(1.f), SoundFXVolume(1.f), bAllowBackgroundAudio(false), bUseHDRAudioMode(false)
{
	
}

UFrontendGameUserSettings* UFrontendGameUserSettings::Get()
{
	if (GEngine)
	{
		return CastChecked<UFrontendGameUserSettings>(GEngine->GetGameUserSettings());
	}
	return nullptr;
}

void UFrontendGameUserSettings::SetOverallVolume(const float InNewVolume)
{
	OverallVolume = InNewVolume;

	// Logic for controlling the volume goes here
}

void UFrontendGameUserSettings::SetMusicVolume(const float InMusicVolume)
{
	MusicVolume = InMusicVolume;
}

void UFrontendGameUserSettings::SetSoundFXVolume(const float InSoundFXVolume)
{
	SoundFXVolume = InSoundFXVolume;
}

void UFrontendGameUserSettings::SetAllowBackgroundAudio(bool InAllowBackgroundAudio)
{
	bAllowBackgroundAudio = InAllowBackgroundAudio;
}

void UFrontendGameUserSettings::SetUseHDRAudioMode(bool InUseHDRAudioMode)
{
	bUseHDRAudioMode = InUseHDRAudioMode;
}
