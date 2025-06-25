// Vince Petrelli


#include "Widgets/Options/DataAsset_DataListEntryMapping.h"

#include "Widgets/Options/DataObjects/ListDataObject_Base.h"

TSubclassOf<UWidget_ListEntry_Base> UDataAsset_DataListEntryMapping::FindEntryWidgetClassByDataObject(
	UListDataObject_Base* InDataObject) const
{
	check(InDataObject);

	// for loop: inicializara DOC, condicion: DOC valido, post loop, DOC es SuperClase
	for (UClass* DataObjectClass = InDataObject->GetClass(); DataObjectClass; DataObjectClass = DataObjectClass->GetSuperClass())
	{
		if (TSubclassOf<UListDataObject_Base> ConvertedDataObjectClass = TSubclassOf<UListDataObject_Base>(DataObjectClass))
		{
			if (DataObjectListEntryMap.Contains(ConvertedDataObjectClass))
			{
				return DataObjectListEntryMap.FindRef(ConvertedDataObjectClass);
			}
		}
	}

	return TSubclassOf<UWidget_ListEntry_Base>();
}
