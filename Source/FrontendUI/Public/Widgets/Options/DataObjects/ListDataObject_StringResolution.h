// Vince Petrelli

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Options/DataObjects/ListDataObject_String.h"
#include "ListDataObject_StringResolution.generated.h"

/**
 * 
 */
UCLASS()
class FRONTENDUI_API UListDataObject_StringResolution : public UListDataObject_String
{
	GENERATED_BODY()

public:

	void InitResolutionValues();
	
};
