// Vince Petrelli


#include "Widgets/Options/Widget_OptionsDetailsView.h"

#include "CommonTextBlock.h"
#include "CommonLazyImage.h"
#include "CommonRichTextBlock.h"
#include "Widgets/Options/DataObjects/ListDataObject_Base.h"

void UWidget_OptionsDetailsView::UpdateDetailsViewInfo(UListDataObject_Base* InDataObject,
                                                       const FString& InEntryWidgetClassName)
{
	if (!InDataObject) return;

	CommonTextBlock_Title->SetText(InDataObject->GetDataDisplayName());
	if (!InDataObject->GetSoftDescriptionImage().IsValid())
	{
		CommonLazyImage_DescriptionImage->SetBrushFromLazyTexture(InDataObject->GetSoftDescriptionImage());
		CommonLazyImage_DescriptionImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		CommonLazyImage_DescriptionImage->SetVisibility(ESlateVisibility::Collapsed);
	}
	
	CommonRichTextBlock_Description->SetText(InDataObject->GetDescriptionRichText());

	const FString DynamicDetails = FString::Printf(
		TEXT("Data Object Class: <Bold>%s</>\n\nEntry Widget Class: <Bold>%s</>"),
		*InDataObject->GetClass()->GetName(),
		*InEntryWidgetClassName
	);
	
	CommonRichTextBlock_DynamicDetails->SetText(FText::FromString(DynamicDetails));
	CommonRichTextBlock_DisabledReason->SetText(InDataObject->GetDisabledRichText());
	
}

void UWidget_OptionsDetailsView::ClearDetailsViewInfo()
{
	CommonTextBlock_Title->SetText(FText::GetEmpty());
	CommonLazyImage_DescriptionImage->SetVisibility(ESlateVisibility::Collapsed);
	CommonRichTextBlock_Description->SetText(FText::GetEmpty());
	CommonRichTextBlock_DynamicDetails->SetText(FText::GetEmpty());
	CommonRichTextBlock_DisabledReason->SetText(FText::GetEmpty());
}

void UWidget_OptionsDetailsView::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	ClearDetailsViewInfo();
}
