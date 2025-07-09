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

	// Should be overriden for gamepad iteraction to work
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Get Widget To Focus For Gamepad"))
	UWidget* BP_GetWidgetToFocusForGamepad() const;

	// Should be overriden to handle highlight state on hovered or selected
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Toggle Entry Widget Highlight State"))
	void BP_OnToggleEntryWidgetHighlightState(bool bShouldHighlight) const;
	
	// ~ Begin IUserObjectListEntry Interface
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	virtual void NativeOnEntryReleased() override;
	virtual void NativeOnItemSelectionChanged(bool bIsSelected) override;
	// ~ End IUserObjectListEntry Interface

	// ~ Begin UUserWidget Interface
	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;
	// ~ End UUserWidget Interface

	// Child should override method to handle initialization. Super call is expected
	virtual void OnOwningListDataObjectSet(UListDataObject_Base* InOwningListDataObject);
	// Child should override to Update UI Values after data modification. Super call is not needed
	virtual void OnOwningListDataObjectModified(UListDataObject_Base* InOwningModifiedData, EOptionsListDataModifyReason ModifyReason);

	virtual void OnOwningDependencyDataObjectModified(UListDataObject_Base* InOwningModifiedDependencyData, EOptionsListDataModifyReason ModifyReason);
	
	// Child should override method to change editable state of owned widgets. Super call is expected
	virtual void OnToggleEditableState(bool bIsEditable);

	void SelectThisEntryWidget();
	
private:

	// ****** Bound Widgets ****** //
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional, AllowPrivateAccess = "true"))
	UCommonTextBlock* CommonText_SettingDisplayName;	
	// ****** Bound Widgets ****** //

	UPROPERTY(Transient)
	UListDataObject_Base* CachedOwningDataObject;
	
};
