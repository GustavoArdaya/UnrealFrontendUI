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
	
protected:

	virtual void Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor) override
	{
		
	}

	virtual bool HandleKeyDownEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent) override
	{
		Debug::Print(TEXT("Pressed Key:") + InKeyEvent.GetKey().GetDisplayName().ToString());

		UEnum* StaticCommonInputType = StaticEnum<ECommonInputType>();		
		Debug::Print(TEXT("Desired Input Key Type: " + StaticCommonInputType->GetValueAsString(CachedInputTypeToListenTo)));
		return true;
	}

	virtual bool HandleMouseButtonDownEvent( FSlateApplication& SlateApp, const FPointerEvent& MouseEvent) override
	{
		Debug::Print(TEXT("Pressed Key:") + MouseEvent.GetEffectingButton().GetDisplayName().ToString());
		return true;
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
