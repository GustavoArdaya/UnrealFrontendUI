// Vince Petrelli

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AsyncAction_PushSoftWidget.generated.h"

class UWidget_ActivatableBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPushSoftWidgetDelegate, UWidget_ActivatableBase*, PushedWidget);
/**
 * 
 */
UCLASS()
class FRONTENDUI_API UAsyncAction_PushSoftWidget : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", HidePin = "WorldContextObject", BlueprintInternalUseOnly = "true", DisplayName = "Push Soft Widget to Widget Stack"))
	static UAsyncAction_PushSoftWidget* PushSoftWidget(const UObject* WorldContextObject,
		APlayerController* OwningPlayerController, TSoftClassPtr<UWidget_ActivatableBase> InSoftWidgetClass,
		UPARAM(meta = (Categories = "Frontend.WidgetStack")) FGameplayTag InWidgetStackTag, bool bFocusOnNewlyPushedWidget = true);

	UPROPERTY(BlueprintAssignable)
	FOnPushSoftWidgetDelegate OnWidgetCreatedBeforePush;

	UPROPERTY(BlueprintAssignable)
	FOnPushSoftWidgetDelegate AfterPush;
};
