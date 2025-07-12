// Vince Petrelli


#include "Widgets/Options/Widget_KeyRemapScreen.h"


#include "CommonInputSubsystem.h"
#include "CommonRichTextBlock.h"
#include "CommonUITypes.h"
#include "ICommonInputModule.h"
#include "Framework/Application/IInputProcessor.h"

class FKeyRemapScreenInputPreprocessor: public IInputProcessor
{

public:

	FKeyRemapScreenInputPreprocessor(ECommonInputType InInputTypeToListenTo, ULocalPlayer* InOwningLocalPlayer)
		: CachedInputTypeToListenTo(InInputTypeToListenTo), CachedWeakOwningLocalPlayer(InOwningLocalPlayer)	
	{}

	DECLARE_DELEGATE_OneParam(FOnInputPreprocessorKeyPressedDelegate, const FKey& /*PressedKey*/);
	FOnInputPreprocessorKeyPressedDelegate OnInputPreprocessorKeyPressed;

	DECLARE_DELEGATE_OneParam(FOnInputPreprocessorKeySelectCanceledDelegate, const FString& /*CanceledReason*/);
	FOnInputPreprocessorKeySelectCanceledDelegate OnInputPreprocessorKeySelectCanceled;
	
protected:

	virtual void Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor) override
	{
		
	}

	virtual bool HandleKeyDownEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent) override
	{
		ProcessPressedKey(InKeyEvent.GetKey());
		
		return true;
	}

	virtual bool HandleMouseButtonDownEvent( FSlateApplication& SlateApp, const FPointerEvent& MouseEvent) override
	{
		ProcessPressedKey(MouseEvent.GetEffectingButton());
		return true;
	}

	void ProcessPressedKey(const FKey& InPressedKey)
	{
		if (InPressedKey == EKeys::Escape)
		{
			OnInputPreprocessorKeySelectCanceled.ExecuteIfBound(TEXT("Key Remap has been canceled"));
			return;
		}

		UCommonInputSubsystem* CommonInputSubsystem = UCommonInputSubsystem::Get(CachedWeakOwningLocalPlayer.Get());

		check(CommonInputSubsystem);

		ECommonInputType CurrentInputType = CommonInputSubsystem->GetCurrentInputType();

		switch (CachedInputTypeToListenTo) {
		case ECommonInputType::MouseAndKeyboard:

			if (InPressedKey.IsGamepadKey() || CurrentInputType == ECommonInputType::Gamepad)
			{
				OnInputPreprocessorKeySelectCanceled.ExecuteIfBound(TEXT("Gamepad Key pressed for Keyboard/Mouse inputs. Key Remap canceled"));
				return;
			}
			break;
		case ECommonInputType::Gamepad:

			if (CurrentInputType == ECommonInputType::Gamepad && InPressedKey == EKeys::LeftMouseButton) // Mapped to face bottom button in UE
			{
				FCommonInputActionDataBase* InputActionData = ICommonInputModule::GetSettings().GetDefaultClickAction().GetRow<FCommonInputActionDataBase>(TEXT(""));
				check(InputActionData);				
				OnInputPreprocessorKeyPressed.ExecuteIfBound(InputActionData->GetDefaultGamepadInputTypeInfo().GetKey());

				return;
			}

				
			if (!InPressedKey.IsGamepadKey())
			{
				OnInputPreprocessorKeySelectCanceled.ExecuteIfBound(TEXT("Non-Gamepad Key pressed for Gamepad inputs. Key Remap canceled"));
				return;
			}
			break;
		default:
			break;
		}

		OnInputPreprocessorKeyPressed.ExecuteIfBound(InPressedKey);
		
	}

private:

	ECommonInputType CachedInputTypeToListenTo;

	TWeakObjectPtr<ULocalPlayer> CachedWeakOwningLocalPlayer;
};

void UWidget_KeyRemapScreen::SetDesiredInputTypeToFilter(ECommonInputType InDesiredInputType)
{
	CachedDesiredInputType = InDesiredInputType;
}

void UWidget_KeyRemapScreen::NativeOnActivated()
{
	Super::NativeOnActivated();

	CachedInputPreprocessor = MakeShared<FKeyRemapScreenInputPreprocessor>(CachedDesiredInputType, GetOwningLocalPlayer());
	CachedInputPreprocessor->OnInputPreprocessorKeyPressed.BindUObject(this, &ThisClass::OnValidKeyPressedDetected);
	CachedInputPreprocessor->OnInputPreprocessorKeySelectCanceled.BindUObject(this, &ThisClass::OnKeySelectCanceled);
	
	FSlateApplication::Get().RegisterInputPreProcessor(CachedInputPreprocessor, -1);

	FString InputDeviceName;

	switch (CachedDesiredInputType) {
	case ECommonInputType::MouseAndKeyboard:
		InputDeviceName = TEXT("Mouse & Keyboard");
		break;
	case ECommonInputType::Gamepad:
		InputDeviceName = TEXT("Gamepad");
		break;
	default:
		break;
	}

	const FString DisplayRichMessage = FString::Printf(
		TEXT("<KeyRemapDefault>Press any</> <KeyRemapHighlight>%s</> <KeyRemapDefault>key. </>"),
		*InputDeviceName
	);
	CommonRichText_RemapMessage->SetText(FText::FromString(DisplayRichMessage));
}

void UWidget_KeyRemapScreen::NativeOnDeactivated()
{
	Super::NativeOnDeactivated();
	if (CachedInputPreprocessor)
	{
		FSlateApplication::Get().UnregisterInputPreProcessor(CachedInputPreprocessor);
		CachedInputPreprocessor.Reset();
	}
}

void UWidget_KeyRemapScreen::OnValidKeyPressedDetected(const FKey& PressedKey)
{
	RequestDeactivateWidget(
		[PressedKey, this]()
		{			
			OnKeyRemapScreenKeyPressed.ExecuteIfBound(PressedKey);
		}
	);
}

void UWidget_KeyRemapScreen::OnKeySelectCanceled(const FString& CanceledReason)
{
	RequestDeactivateWidget(
		[CanceledReason, this]()
		{			
			OnKeyRemapScreenKeySelectCanceled.ExecuteIfBound(CanceledReason);
		}
	);
}

void UWidget_KeyRemapScreen::RequestDeactivateWidget(TFunction<void()> PreDeactivateCallback)
{
	// Delay a tick
	FTSTicker::GetCoreTicker().AddTicker(
		FTickerDelegate::CreateLambda(
			[PreDeactivateCallback, this](float DeltaTime)->bool
			{
				PreDeactivateCallback();
				DeactivateWidget();
				return false; // false allows "reticking" back to normal
			}
		)
	);
}
