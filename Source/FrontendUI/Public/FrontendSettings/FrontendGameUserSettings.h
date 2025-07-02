// Vince Petrelli

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "FrontendGameUserSettings.generated.h"

/**
 * 
 */
UCLASS()
class FRONTENDUI_API UFrontendGameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()

public:

	UFrontendGameUserSettings();

	static UFrontendGameUserSettings* Get();
	
	// ***** Gameplay Collection Tab ***** //
	UFUNCTION()
	FORCEINLINE FString GetCurrentGameDifficulty() const { return CurrentGameDifficulty; }
	UFUNCTION()
	FORCEINLINE void SetCurrentGameDifficulty(const FString& InNewDifficulty) { CurrentGameDifficulty = InNewDifficulty; }
	// ***** Gameplay Collection Tab ***** //

	// ***** Audio Collection Tab ***** //
	UFUNCTION()
	FORCEINLINE float GetOverallVolume() const { return OverallVolume; }
	UFUNCTION()
	void SetOverallVolume(const float InNewVolume);

	UFUNCTION()
	FORCEINLINE float GetMusicVolume() const { return MusicVolume; }
	UFUNCTION()
	void SetMusicVolume(const float InMusicVolume);

	UFUNCTION()
	FORCEINLINE float GetSoundFXVolume() const { return SoundFXVolume; }
	UFUNCTION()
	void SetSoundFXVolume(const float InSoundFXVolume);

	UFUNCTION()
	FORCEINLINE bool GetAllowBackgroundAudio() const { return bAllowBackgroundAudio; }
	UFUNCTION()
	void SetAllowBackgroundAudio(bool InAllowBackgroundAudio);

	UFUNCTION()
	FORCEINLINE bool GetUseHDRAudioMode() const { return bUseHDRAudioMode; }
	UFUNCTION()
	void SetUseHDRAudioMode(bool InUseHDRAudioMode);

	
	// ***** Audio Collection Tab ***** //
private:

	// ***** Gameplay Collection Tab ***** //
	UPROPERTY(Config)
	FString CurrentGameDifficulty;
	// ***** Gameplay Collection Tab ***** //

	// ***** Audio Collection Tab ***** //
	UPROPERTY(Config)
	float OverallVolume;

	UPROPERTY(Config)
	float MusicVolume;

	UPROPERTY(Config)
	float SoundFXVolume;

	UPROPERTY(Config)
	bool bAllowBackgroundAudio;

	UPROPERTY(Config)
	bool bUseHDRAudioMode;
	// ***** Audio Collection Tab ***** //
	
};
