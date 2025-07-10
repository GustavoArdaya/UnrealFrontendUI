// Vince Petrelli


#include "Widgets/Options/Widget_KeyRemapScreen.h"


#include "CommonRichTextBlock.h"
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
	
}

void UWidget_KeyRemapScreen::OnKeySelectCanceled(const FString& CanceledReason)
{
}
