// Vince Petrelli


#include "Widgets/Options/DataObjects/ListDataObject_Scalar.h"

#include "Widgets/Options/OptionsDataInteractionHelper.h"

FCommonNumberFormattingOptions UListDataObject_Scalar::NoDecimal()
{
	FCommonNumberFormattingOptions Options;
	Options.MaximumFractionalDigits = 0;

	return Options;
}

FCommonNumberFormattingOptions UListDataObject_Scalar::WithDecimal(int32 NumFracDigit)
{
	FCommonNumberFormattingOptions Options;
	Options.MaximumFractionalDigits = NumFracDigit;

	return Options;
}

float UListDataObject_Scalar::GetCurrentValue() const
{
	if (DataDynamicGetter.IsValid())
	{
		return FMath::GetMappedRangeValueClamped(
			OutputValueRange,
			DisplayValueRange,
			StringToFloat(DataDynamicGetter->GetValueAsString())
		);
	}

	return 0.f;
}

void UListDataObject_Scalar::SetCurrentValueFromSlider(float InValue)
{
	if (DataDynamicSetter.IsValid())
	{
		const float ClampedValue = FMath::GetMappedRangeValueClamped(
			DisplayValueRange,
			OutputValueRange,
			InValue);
		DataDynamicSetter->SetValueFromString(LexToString(ClampedValue));
		NotifyListDataModified(this);
	}
}

float UListDataObject_Scalar::StringToFloat(const FString& InString) const
{
	float OutConvertedValue = 0.f;
	LexFromString(OutConvertedValue, *InString);

	return OutConvertedValue;
}
