#include "W_CurrencyContainer.h"

void UW_CurrencyContainer::NativeConstruct()
{
	Super::NativeConstruct();
	RefreshCurrencies();
}

void UW_CurrencyContainer::RefreshCurrencies()
{
	OnRefreshCurrencies();
}
