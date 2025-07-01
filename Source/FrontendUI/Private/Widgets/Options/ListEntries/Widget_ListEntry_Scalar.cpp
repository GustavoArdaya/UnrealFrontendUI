// Vince Petrelli


#include "Widgets/Options/ListEntries/Widget_ListEntry_Scalar.h"

void UWidget_ListEntry_Scalar::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
}

void UWidget_ListEntry_Scalar::OnOwningListDataObjectSet(UListDataObject_Base* InOwningListDataObject)
{
	Super::OnOwningListDataObjectSet(InOwningListDataObject);
}

void UWidget_ListEntry_Scalar::OnOwningListDataObjectModified(UListDataObject_Base* IOwningModifiedDat,
	EOptionsListDataModifyReason ModifyReason)
{
	
}
