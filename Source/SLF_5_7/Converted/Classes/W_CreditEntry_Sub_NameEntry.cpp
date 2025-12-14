#include "W_CreditEntry_Sub_NameEntry.h"

void UW_CreditEntry_Sub_NameEntry::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (NameText && !Name.IsEmpty())
	{
		NameText->SetText(Name);
	}
}

void UW_CreditEntry_Sub_NameEntry::SetName(FText InName)
{
	Name = InName;

	if (NameText)
	{
		NameText->SetText(Name);
	}
}
