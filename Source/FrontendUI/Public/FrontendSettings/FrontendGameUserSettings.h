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
	// ***** Audio Collection Tab ***** //
private:

	// ***** Gameplay Collection Tab ***** //
	UPROPERTY(Config)
	FString CurrentGameDifficulty;
	// ***** Gameplay Collection Tab ***** //

	// ***** Audio Collection Tab ***** //
	UPROPERTY(Config)
	float OverallVolume;
	// ***** Audio Collection Tab ***** //
	
};
