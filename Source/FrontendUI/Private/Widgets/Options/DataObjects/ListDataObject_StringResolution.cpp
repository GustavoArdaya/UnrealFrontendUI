// Vince Petrelli


#include "Widgets/Options/DataObjects/ListDataObject_StringResolution.h"

#include "FrontendDebugHelper.h"
#include "FrontendSettings/FrontendGameUserSettings.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Widgets/Options/OptionsDataInteractionHelper.h"

void UListDataObject_StringResolution::InitResolutionValues()
{
	TArray<FIntPoint> AvailableScreenResolutions;
	UKismetSystemLibrary::GetSupportedFullscreenResolutions(AvailableScreenResolutions);
	AvailableScreenResolutions.Sort(
		[](const FIntPoint& A, const FIntPoint& B)->bool
		{
			return A.SizeSquared() < B.SizeSquared();
		}
	);
	
	for (const FIntPoint &Resolution : AvailableScreenResolutions)
	{
		AddDynamicOption(ResToValueString(Resolution), ResToDisplayText(Resolution));
	}

	MaxAllowedResolution = ResToValueString(AvailableScreenResolutions.Last());

	SetDefaultValueFromString(MaxAllowedResolution);
}

void UListDataObject_StringResolution::OnDataObjectInitialized()
{
	Super::OnDataObjectInitialized();

	if (!TrySetDisplayTextFromStringValue(CurrentStringValue))
	{
		CurrentDisplayText = ResToDisplayText(UFrontendGameUserSettings::Get()->GetScreenResolution());
	}
}

FString UListDataObject_StringResolution::ResToValueString(const FIntPoint& InResolution) const
{
	// Resolution Value from Dynamic Getter: (X=2560,Y=1440)
	return FString::Printf(TEXT("X=%i,Y=%i)"), InResolution.X, InResolution.Y);
}

FText UListDataObject_StringResolution::ResToDisplayText(const FIntPoint& InResolution) const
{
	const FString DisplayString = FString::Printf(TEXT("%i x %i"), InResolution.X, InResolution.Y);
	return FText::FromString(DisplayString);
}
