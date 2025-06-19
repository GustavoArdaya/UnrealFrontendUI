// Vince Petrelli


#include "FrontendFunctionLibrary.h"
#include "FrontendSettings/FrontendDeveloperSettings.h"
#include "GameplayTagContainer.h"

TSoftClassPtr<UWidget_ActivatableBase> UFrontendFunctionLibrary::GetFrontendSoftWidgetClassByTag(
	UPARAM(meta = (Categories = "Frontend.Widget")) FGameplayTag InWidgetTag)
{
	const UFrontendDeveloperSettings* FrontendDeveloperSettings = GetDefault<UFrontendDeveloperSettings>();
	checkf(FrontendDeveloperSettings->FrontendWidgetMap.Contains(InWidgetTag), TEXT("Could not find corresponding widget under tag %s"), *InWidgetTag.ToString());
	return FrontendDeveloperSettings->FrontendWidgetMap.FindRef(InWidgetTag);
}
