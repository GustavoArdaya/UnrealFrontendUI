// Vince Petrelli


#include "Widgets/Options/DataObjects/ListDataObject_KeyRemap.h"

#include "CommonInputBaseTypes.h"
#include "CommonInputSubsystem.h"
#include "FrontendDebugHelper.h"

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

FSlateBrush UListDataObject_KeyRemap::GetIconFromCurrentKey() const
{
	check(CachedOwningInputUserSettings)
	FSlateBrush FoundBrush;

	UCommonInputSubsystem* CommonInputSubsystem = UCommonInputSubsystem::Get(CachedOwningInputUserSettings->GetLocalPlayer());
	check(CommonInputSubsystem);
	
	const bool bHasFoundBrush = UCommonInputPlatformSettings::Get()->TryGetInputBrush(
		FoundBrush,
		GetOwningKeyMapping()->GetCurrentKey(),
		CachedDesiredInputKeyType,
		CommonInputSubsystem->GetCurrentGamepadName()
	);

	if (!bHasFoundBrush)
	{
		Debug::Print(TEXT("Unable to find an icon for key ") +
			GetOwningKeyMapping()->GetCurrentKey().GetDisplayName().ToString() +
			TEXT(". Empty brush was applied.")
		);
	}
	return FoundBrush;
}

void UListDataObject_KeyRemap::BindNewInputKey(const FKey& NewInputKey)
{
	check(CachedOwningInputUserSettings)

	FMapPlayerKeyArgs KeyArgs;
	KeyArgs.MappingName = CachedOwningMappingName;
	KeyArgs.Slot = CachedOwningMappableKeySlot;
	KeyArgs.NewKey = NewInputKey;

	FGameplayTagContainer Container;
	
	CachedOwningInputUserSettings->MapPlayerKey(KeyArgs, Container );
	CachedOwningInputUserSettings->SaveSettings();

	NotifyListDataModified(this);
}

bool UListDataObject_KeyRemap::HasDefaultValue() const
{
	return GetOwningKeyMapping()->GetDefaultKey().IsValid();
}

bool UListDataObject_KeyRemap::CanResetBackToDefaultValue() const
{
	return HasDefaultValue() && GetOwningKeyMapping()->IsCustomized();
		
}

bool UListDataObject_KeyRemap::TryResetBackToDefaultValue()
{
	if (CanResetBackToDefaultValue())
	{
		check(CachedOwningInputUserSettings);
		
		GetOwningKeyMapping()->ResetToDefault();		
		CachedOwningInputUserSettings->SaveSettings();
		NotifyListDataModified(this, EOptionsListDataModifyReason::ResetToDefault);

		return true;
	}
	return false;
}

FPlayerKeyMapping* UListDataObject_KeyRemap::GetOwningKeyMapping() const
{
	check(CachedOwningKeyProfile);

	FMapPlayerKeyArgs KeyArgs;
	KeyArgs.MappingName = CachedOwningMappingName;
	KeyArgs.Slot = CachedOwningMappableKeySlot;

	return CachedOwningKeyProfile->FindKeyMapping(KeyArgs);
}
