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

private:

	UPROPERTY(Config)
	FString CurrentGameDifficulty;
	
};
