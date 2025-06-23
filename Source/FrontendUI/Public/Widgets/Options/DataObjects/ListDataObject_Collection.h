// Vince Petrelli

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Options/DataObjects/ListDataObject_Base.h"
#include "ListDataObject_Collection.generated.h"

/**
 * 
 */
UCLASS()
class FRONTENDUI_API UListDataObject_Collection : public UListDataObject_Base
{
	GENERATED_BODY()

public:

	void AddChildListData(UListDataObject_Base* InChildListData);

	// ~ Begin UListDataObject_Base Interface
	FORCEINLINE virtual TArray<UListDataObject_Base*> GetAllChildListData() const override;
	virtual bool HasAnyChildListData() const override;
	// ~ End UListDataObject_Base Interface
	
private:

	UPROPERTY(Transient)
	TArray<UListDataObject_Base*> ChildListDataArray;
	
};
