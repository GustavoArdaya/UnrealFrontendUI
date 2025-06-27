// Vince Petrelli

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "FrontendTypes/FrontendEnumTypes.h"
#include "Widget_ListEntry_Base.generated.h"

class UListDataObject_Base;
class UCommonTextBlock;
/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNaiveTick))
class FRONTENDUI_API UWidget_ListEntry_Base : public UCommonUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On List Entry Widget Hovered"))
	void BP_OnListEntryWidgetHovered(bool bWasHovered, bool bIsEntryWidgetStillSelected);
	
	void NativeOnListEntryWidgetHovered(bool bWasHovered);

protected:

	// ~ Begin IUserObjectListEntry Interface
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	// ~ End IUserObjectListEntry Interface

	// Child should override method to handle initialization. Super call is expected
	virtual void OnOwningListDataObjectSet(UListDataObject_Base* InOwningListDataObject);
	// Child should override to Update UI Values after data modification. Super call is not needed
	virtual void OnOwningListDataObjectModified(UListDataObject_Base* IOwningModifiedDat, EOptionsListDataModifyReason ModifyReason);

private:

	// ****** Bound Widgets ****** //
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, AllowPrivateAccess = "true"))
	UCommonTextBlock* CommonText_SettingDisplayName;
	
	// ****** Bound Widgets ****** //
	
};
