// Vince Petrelli

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Options/DataObjects/ListDataObject_Value.h"
#include "ListDataObject_String.generated.h"

/**
 * 
 */
UCLASS()
class FRONTENDUI_API UListDataObject_String : public UListDataObject_Value
{
	GENERATED_BODY()

public:

	void AddDynamicOption(const FString& InStringValue, const FText& InDisplayText);

protected:

	// ~ Begin UListDataObject_Base Interface
	virtual void OnDataObjectInitialized() override;
	// ~ End UListDataObject_Base Interface

	bool TrySetDisplayTextFromStringValue(const FString& InStringValue);

	FString CurrentStringValue;
	FText CurrentDisplayText;
	TArray<FString> AvailableOptionsStringArray;
	TArray<FText> AvailableOptionsTextArray;
	
	
};
