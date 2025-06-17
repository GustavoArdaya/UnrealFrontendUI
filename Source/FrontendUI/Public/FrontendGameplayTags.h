// Vince Petrelli

#pragma once

#include "NativeGameplayTags.h"
#include "CoreMinimal.h"

/*/**
 * 
 #1#
class FRONTENDUI_API FrontendGameplayTags
{
public:
	FrontendGameplayTags();
	~FrontendGameplayTags();
};*/
namespace FrontEndGameplayTags
{
	FRONTENDUI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_WidgetStack_Modal);
	FRONTENDUI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_WidgetStack_GameMenu);
	FRONTENDUI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_WidgetStack_GameHud);
	FRONTENDUI_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Frontend_WidgetStack_FrontEnd);
}
