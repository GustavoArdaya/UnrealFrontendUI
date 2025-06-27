// Vince Petrelli


#include "Widgets/Options/ListEntries/Widget_ListEntry_String.h"

#include "FrontendDebugHelper.h"
#include "Widgets/Components/FrontendCommonButtonBase.h"
#include "Widgets/Components/FrontendCommonRotator.h"
#include "Widgets/Options/DataObjects/ListDataObject_String.h"

void UWidget_ListEntry_String::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CommonButton_PreviousOption->OnClicked().AddUObject(this, &ThisClass::OnPreviousOptionButtonClicked);
	CommonButton_NextOption->OnClicked().AddUObject(this, &ThisClass::OnNextOptionButtonClicked);
	
	CommonRotator_AvailableOptions->OnClicked().AddLambda([this]()
	{
		SelectThisEntryWidget();
	});
}

void UWidget_ListEntry_String::OnOwningListDataObjectSet(UListDataObject_Base* InOwningListDataObject)
{
	Super::OnOwningListDataObjectSet(InOwningListDataObject);

	CachedOwningStringDataObject = CastChecked<UListDataObject_String>(InOwningListDataObject);

	CommonRotator_AvailableOptions->PopulateTextLabels(CachedOwningStringDataObject->GetAvailableOptionsTextArray());
	CommonRotator_AvailableOptions->SetSelectedOptionByText(CachedOwningStringDataObject->GetCurrentDisplayText());
}

void UWidget_ListEntry_String::OnOwningListDataObjectModified(UListDataObject_Base* IOwningModifiedDat,
	EOptionsListDataModifyReason ModifyReason)
{
	Super::OnOwningListDataObjectModified(IOwningModifiedDat, ModifyReason);
	if (CachedOwningStringDataObject)
	{
		CommonRotator_AvailableOptions->SetSelectedOptionByText(CachedOwningStringDataObject->GetCurrentDisplayText());
	}
		
}

void UWidget_ListEntry_String::OnPreviousOptionButtonClicked()
{
	if (CachedOwningStringDataObject)
	{
		CachedOwningStringDataObject->GoToPreviousOption();
	}

	SelectThisEntryWidget();
}

void UWidget_ListEntry_String::OnNextOptionButtonClicked()
{
	if (CachedOwningStringDataObject)
	{
		CachedOwningStringDataObject->GoToNextOption();
	}

	SelectThisEntryWidget();
}
