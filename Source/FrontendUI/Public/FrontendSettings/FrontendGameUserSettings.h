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

	static UFrontendGameUserSettings* Get();
	
	// ***** Gameplay Collection Tab ***** //
	UFUNCTION()
	FORCEINLINE FString GetCurrentGameDifficulty() const { return CurrentGameDifficulty; }
	UFUNCTION()
	FORCEINLINE void SetCurrentGameDifficulty(const FString& InNewDifficulty) { CurrentGameDifficulty = InNewDifficulty; }
	// ***** Gameplay Collection Tab ***** //

private:

	UPROPERTY(Config)
	FString CurrentGameDifficulty;
	
};
