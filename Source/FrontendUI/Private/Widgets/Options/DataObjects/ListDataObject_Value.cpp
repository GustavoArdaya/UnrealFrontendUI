// Vince Petrelli


#include "Widgets/Options/DataObjects/ListDataObject_Value.h"

void UListDataObject_Value::SetDataDynamicGetter(const TSharedPtr<FOptionsDataInteractionHelper>& InDynamicGetter)
{
	DataDynamicGetter = InDynamicGetter;
}

void UListDataObject_Value::SetDataDynamicSetter(const TSharedPtr<FOptionsDataInteractionHelper>& InDynamicSetter)
{
	DataDynamicSetter = InDynamicSetter;
}
