#include "W_CreditEntry_Extra.h"

void UW_CreditEntry_Extra::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (ExtraText && !ExtraContent.IsEmpty())
	{
		ExtraText->SetText(ExtraContent);
	}
}

void UW_CreditEntry_Extra::SetupExtraEntry(const FCreditsExtra& ExtraData)
{
	ExtraContent = ExtraData.Text;

	if (ExtraText)
	{
		ExtraText->SetText(ExtraContent);
	}
}
