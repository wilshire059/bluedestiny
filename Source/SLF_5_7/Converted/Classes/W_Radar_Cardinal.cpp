#include "W_Radar_Cardinal.h"

void UW_Radar_Cardinal::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (CardinalText && !CardinalData.UIDisplayText.IsEmpty())
	{
		CardinalText->SetText(FText::FromString(CardinalData.UIDisplayText));
	}
}

void UW_Radar_Cardinal::SetupCardinal(const FCardinalData& Data)
{
	CardinalData = Data;

	if (CardinalText)
	{
		CardinalText->SetText(FText::FromString(Data.UIDisplayText));
	}
}
