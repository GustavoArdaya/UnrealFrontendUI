// Vince Petrelli

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Options/ListEntries/Widget_ListEntry_Base.h"
#include "Widget_ListEntry_KeyRemap.generated.h"

class UListDataObject_KeyRemap;
class UFrontendCommonButtonBase;
/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNaiveTick))
class FRONTENDUI_API UWidget_ListEntry_KeyRemap : public UWidget_ListEntry_Base
{
	GENERATED_BODY()

protected:

	// ~ Begin UWidget_ListEntry_Base Interface
	virtual void OnOwningListDataObjectSet(UListDataObject_Base* InOwningListDataObject) override;
	virtual void OnOwningListDataObjectModified(UListDataObject_Base* InOwningModifiedData, EOptionsListDataModifyReason ModifyReason) override;
	// ~ End UWidget_ListEntry_Base Interface

private:

	// ***** Bound Widgets ***** //
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	UFrontendCommonButtonBase* CommonButton_RemapKey;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	UFrontendCommonButtonBase* CommonButton_ResetKeyBinding;
	// ***** Bound Widgets ***** //

	UPROPERTY(Transient)
	UListDataObject_KeyRemap* CachedOwningKeyRemapDataObject;
	
};
