// Vince Petrelli


#include "FrontendSettings/FrontendGameUserSettings.h"

UFrontendGameUserSettings::UFrontendGameUserSettings()
	: OverallVolume(1.f)
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
