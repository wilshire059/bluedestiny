#include "W_CreditEntry_Sub.h"

void UW_CreditEntry_Sub::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (CategoryText && !Category.IsEmpty())
	{
		CategoryText->SetText(Category);
	}
}

void UW_CreditEntry_Sub::SetupSubEntry(FText InCategory, const TArray<FText>& Names)
{
	Category = InCategory;

	if (CategoryText)
	{
		CategoryText->SetText(Category);
	}

	OnSetupNames(Names);
}
