// Vince Petrelli

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Options/DataObjects/ListDataObject_Base.h"
#include "ListDataObject_Value.generated.h"

class FOptionsDataInteractionHelper;
/**
 * 
 */
UCLASS(Abstract)
class FRONTENDUI_API UListDataObject_Value : public UListDataObject_Base
{
	GENERATED_BODY()

public:

	void SetDataDynamicGetter(const TSharedPtr<FOptionsDataInteractionHelper>& InDynamicGetter);
	void SetDataDynamicSetter(const TSharedPtr<FOptionsDataInteractionHelper>& InDynamicSetter);

	FORCEINLINE void SetDefaultValueFromString(const FString& InDefaultValue) { DefaultStringValue = InDefaultValue; }

	// ~ Begin UListDataObject_Base Interface
	FORCEINLINE virtual bool HasDefaultValue() const override { return DefaultStringValue.IsSet(); }
	// ~ End UListDataObject_Base Interface
	
protected:

	FORCEINLINE	FString GetDefaultValueAsString() const { return DefaultStringValue.GetValue(); }
	
	TSharedPtr<FOptionsDataInteractionHelper> DataDynamicGetter;
	TSharedPtr<FOptionsDataInteractionHelper> DataDynamicSetter;

private:

	TOptional<FString> DefaultStringValue;
	
};
