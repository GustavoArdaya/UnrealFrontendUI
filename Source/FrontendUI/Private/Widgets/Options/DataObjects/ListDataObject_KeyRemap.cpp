// Vince Petrelli


#include "Widgets/Options/DataObjects/ListDataObject_KeyRemap.h"

void UListDataObject_KeyRemap::InitKeyRemapData(UEnhancedInputUserSettings* InOwningInputUserSettings,
	UEnhancedPlayerMappableKeyProfile* InKeyProfile, ECommonInputType InDesiredInputKeyType,
	const FPlayerKeyMapping& InOwningPlayerKeyMapping)
{
	CachedOwningInputUserSettings = InOwningInputUserSettings;
	CachedOwningKeyProfile = InKeyProfile;
	CachedDesiredInputKeyType = InDesiredInputKeyType;
	CachedOwningMappingName = InOwningPlayerKeyMapping.GetMappingName();
	CachedOwningMappableKeySlot = InOwningPlayerKeyMapping.GetSlot();
}
