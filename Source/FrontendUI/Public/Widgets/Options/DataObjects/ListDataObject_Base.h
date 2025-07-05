// Vince Petrelli

#pragma once

#include "CoreMinimal.h"
#include "FrontendTypes/FrontendEnumTypes.h"
#include "FrontendTypes/FrontendStructTypes.h"
#include "ListDataObject_Base.generated.h"

#define LIST_DATA_ACCESSOR(DataType, PropertyName) \
	FORCEINLINE DataType Get##PropertyName() const { return PropertyName; } \
	FORCEINLINE void Set##PropertyName(DataType In##PropertyName) { PropertyName = In##PropertyName; }
	
/**
 * 
 */
UCLASS(Abstract)
class FRONTENDUI_API UListDataObject_Base : public UObject
{
	GENERATED_BODY()

public:

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnListDataModifiedDelegate, UListDataObject_Base*, EOptionsListDataModifyReason);
	FOnListDataModifiedDelegate OnListDataModified;
	FOnListDataModifiedDelegate OnDependencyDataModified;

	LIST_DATA_ACCESSOR(FName, DataID)
	LIST_DATA_ACCESSOR(FText, DataDisplayName)
	LIST_DATA_ACCESSOR(FText, DescriptionRichText)
	LIST_DATA_ACCESSOR(FText, DisabledRichText)
	LIST_DATA_ACCESSOR(TSoftObjectPtr<UTexture2D>, SoftDescriptionImage)
	LIST_DATA_ACCESSOR(UListDataObject_Base*, ParentData)

	void InitDataObject();

	// Empty in the base class. Derived classes have to override these functions
	FORCEINLINE virtual TArray<UListDataObject_Base*> GetAllChildListData() const { return TArray<UListDataObject_Base*>(); }
	virtual bool HasAnyChildListData() const { return false; }

	FORCEINLINE void SetShouldApplySettingsImmediately(bool bShouldApplyRightAway) { bShouldApplyChangeImmediately = bShouldApplyRightAway; }

	// Should be overriden to provide reset data implementation
	virtual bool HasDefaultValue() const { return false; }
	virtual bool CanResetBackToDefaultValue() const { return false; }
	virtual bool TryResetBackToDefaultValue() { return false; }

	// Called from OptionsDataRegister for adding in edit conditions for the list data object
	void AddEditCondition(const FOptionsDataEditConditionDescriptor& InEditCondition);
	
	// Called from OptionsDataRegister for adding dependencies between the list data objects
	void AddEditDependencyData(UListDataObject_Base* InDependencyData);

	bool IsDataCurrentlyEditable();

protected:

	// Empty in base class. Child should override to handle initialization
	virtual void OnDataObjectInitialized();

	virtual void NotifyListDataModified(UListDataObject_Base* ModifiedData, EOptionsListDataModifyReason ModifyReason = EOptionsListDataModifyReason::DirectlyModified);

	// Should be overriden to allow the value to be set to a forced string value
	virtual bool CanSetToForcedStringValue(const FString& InForcedValue) const { return false; }

	// Should be overriden to specify method of setting current value to forced value
	virtual void OnSetToForcedStringValue(const FString& InForcedValue) {}

	virtual void OnEditDependencyDataModified(UListDataObject_Base* ModifiedDependencyData, EOptionsListDataModifyReason ModifyReason);
	
private:

	FName DataID;
	FText DataDisplayName;
	FText DescriptionRichText;
	FText DisabledRichText;
	TSoftObjectPtr<UTexture2D> SoftDescriptionImage;

	UPROPERTY(Transient)
	UListDataObject_Base* ParentData;

	bool bShouldApplyChangeImmediately = false;

	UPROPERTY(Transient)
	TArray<FOptionsDataEditConditionDescriptor> EditConditionDescArray;
};
