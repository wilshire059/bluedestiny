#include "W_Inventory_ActionButton.h"

void UW_Inventory_ActionButton::NativeConstruct()
{
	Super::NativeConstruct();

	if (ActionText)
	{
		ActionText->SetText(ActionName);
	}

	if (ActionButton)
	{
		ActionButton->OnClicked.AddDynamic(this, &UW_Inventory_ActionButton::HandleButtonClicked);
	}
}

void UW_Inventory_ActionButton::HandleButtonClicked()
{
	OnActionButtonClicked.Broadcast(ActionIndex);
}
