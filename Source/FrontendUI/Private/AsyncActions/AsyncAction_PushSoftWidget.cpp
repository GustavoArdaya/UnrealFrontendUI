// Vince Petrelli


#include "AsyncActions/AsyncAction_PushSoftWidget.h"

#include "Subsystems/FrontendUISubsystem.h"
#include "Widgets/Widget_ActivatableBase.h"

UAsyncAction_PushSoftWidget* UAsyncAction_PushSoftWidget::PushSoftWidget(const UObject* WorldContextObject,
                                                                         APlayerController* OwningPlayerController, TSoftClassPtr<UWidget_ActivatableBase> InSoftWidgetClass,
                                                                         UPARAM(meta = (Categories = "Frontend.WidgetStack")) FGameplayTag InWidgetStackTag, bool bFocusOnNewlyPushedWidget)
{
	checkf(!InSoftWidgetClass.IsNull(), TEXT("PushSoftWidgetToStack was passed with a null soft widget class"));

	if (GEngine)
	{
		if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
		{
			UAsyncAction_PushSoftWidget* Node = NewObject<UAsyncAction_PushSoftWidget>();
			Node->CachedOwningWorld = World;
			Node->CachedOwningPlayerController = OwningPlayerController;
			Node->CachedSoftWidgetClass	= InSoftWidgetClass;
			Node->CachedWidgetStackTag = InWidgetStackTag;
			Node->bCachedFocusOnNewlyPushedWidget = bFocusOnNewlyPushedWidget;
			
			Node->RegisterWithGameInstance(World);
			return Node;
		}
	}

	return nullptr;
}

void UAsyncAction_PushSoftWidget::Activate()
{
	if (UFrontendUISubsystem* FrontendUISubsystem = UFrontendUISubsystem::Get(CachedOwningWorld.Get()))
	{
		FrontendUISubsystem->PushSoftWidgetToStackAsync(
			CachedWidgetStackTag, CachedSoftWidgetClass,
			[this](EAsyncPushWidgetState InPushState, UWidget_ActivatableBase* PushedWidget)
			{
				switch (InPushState)
				{
				case EAsyncPushWidgetState::OnCreatedBeforePush:
					PushedWidget->SetOwningPlayer(CachedOwningPlayerController.Get());
					OnWidgetCreatedBeforePush.Broadcast(PushedWidget);
					break;
				case EAsyncPushWidgetState::AfterPush:
					AfterPush.Broadcast(PushedWidget);
					if (bCachedFocusOnNewlyPushedWidget)
					{
						if (UWidget* WidgetToFocus = PushedWidget->GetDesiredFocusTarget())
						{
							WidgetToFocus->SetFocus();
						}
					}
					SetReadyToDestroy();
					break;
				default:
					break;
				}
			}
		);
	}
}
