// Vince Petrelli

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FrontendFunctionLibrary.generated.h"

struct FGameplayTag;
class UWidget_ActivatableBase;
/**
 * 
 */
UCLASS()
class FRONTENDUI_API UFrontendFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "Frontend Function Library")
	static TSoftClassPtr<UWidget_ActivatableBase> GetFrontendSoftWidgetClassByTag(UPARAM(meta = (Categories = "Frontend.Widget")) FGameplayTag InWidgetTag);
	
};
