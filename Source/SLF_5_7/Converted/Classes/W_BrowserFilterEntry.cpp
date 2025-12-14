#include "W_BrowserFilterEntry.h"

void UW_BrowserFilterEntry::NativeConstruct()
{
	Super::NativeConstruct();

	if (FilterCheckBox)
	{
		FilterCheckBox->OnCheckStateChanged.AddDynamic(this, &UW_BrowserFilterEntry::HandleFilterChanged);
	}
}

void UW_BrowserFilterEntry::SetupFilter(int32 InFilterIndex, FText FilterName, bool bInitialValue)
{
	FilterIndex = InFilterIndex;

	if (FilterNameText)
	{
		FilterNameText->SetText(FilterName);
	}

	if (FilterCheckBox)
	{
		FilterCheckBox->SetIsChecked(bInitialValue);
	}
}

void UW_BrowserFilterEntry::HandleFilterChanged(bool bIsChecked)
{
	OnBrowserFilterChanged.Broadcast(FilterIndex, bIsChecked);
}
