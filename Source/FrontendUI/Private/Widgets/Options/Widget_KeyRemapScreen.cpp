// Vince Petrelli


#include "Widgets/Options/Widget_KeyRemapScreen.h"


#include "FrontendDebugHelper.h"
#include "Framework/Application/IInputProcessor.h"

class FKeyRemapScreenInputPreprocessor: public IInputProcessor
{

public:

	FKeyRemapScreenInputPreprocessor(ECommonInputType InInputTypeToListenTo)
		: CachedInputTypeToListenTo(InInputTypeToListenTo)
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

		switch (CachedInputTypeToListenTo) {
		case ECommonInputType::MouseAndKeyboard:

			if (InPressedKey.IsGamepadKey())
			{
				OnInputPreprocessorKeySelectCanceled.ExecuteIfBound(TEXT("Gamepad Key pressed for Keyboard/Mouse inputs. Key Remap canceled"));
				return;
			}
			break;
		case ECommonInputType::Gamepad:
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
};

void UWidget_KeyRemapScreen::SetDesiredInputTypeToFilter(ECommonInputType InDesiredInputType)
{
	CachedDesiredInputType = InDesiredInputType;
}

void UWidget_KeyRemapScreen::NativeOnActivated()
{
	Super::NativeOnActivated();

	CachedInputPreprocessor = MakeShared<FKeyRemapScreenInputPreprocessor>(CachedDesiredInputType);
	FSlateApplication::Get().RegisterInputPreProcessor(CachedInputPreprocessor, -1);
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
