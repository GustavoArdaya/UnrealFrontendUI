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
	FORCEINLINE float GetSFXVolume() const { return SFXVolume; }
	UFUNCTION()
	void SetSFXVolume(const float InSFXVolume);
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
	float SFXVolume;
	// ***** Audio Collection Tab ***** //
	
};
