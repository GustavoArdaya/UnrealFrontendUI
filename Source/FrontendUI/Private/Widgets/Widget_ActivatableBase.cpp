// Vince Petrelli


#include "Widgets/Widget_ActivatableBase.h"
#include "Controllers/FrontendPlayerController.h"

AFrontendPlayerController* UWidget_ActivatableBase::GetOwningFrontendPlayerController()
{
	if (!CachedOwningFrontendPlayerController.IsValid())
	{
		CachedOwningFrontendPlayerController = GetOwningPlayer<AFrontendPlayerController>();
	}

	return CachedOwningFrontendPlayerController.IsValid() ? CachedOwningFrontendPlayerController.Get() : nullptr;
}
