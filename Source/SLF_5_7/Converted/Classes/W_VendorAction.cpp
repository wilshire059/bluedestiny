#include "W_VendorAction.h"

void UW_VendorAction::NativeConstruct()
{
	Super::NativeConstruct();

	if (ActionButton)
	{
		ActionButton->OnClicked.AddDynamic(this, &UW_VendorAction::HandleActionClicked);
	}
}

void UW_VendorAction::SetupAction(int32 InActionType, FText ActionLabel, int64 Price)
{
	ActionType = InActionType;

	if (ActionText)
	{
		ActionText->SetText(ActionLabel);
	}

	if (PriceText)
	{
		PriceText->SetText(FText::AsNumber(Price));
	}
}

void UW_VendorAction::HandleActionClicked()
{
	OnVendorActionClicked.Broadcast(ActionType);
}

void UW_VendorAction::SetCanAfford(bool bCanAfford)
{
	if (ActionButton)
	{
		ActionButton->SetIsEnabled(bCanAfford);
	}

	if (PriceText)
	{
		FSlateColor Color = bCanAfford ? FSlateColor(FLinearColor::White) : FSlateColor(FLinearColor::Red);
		PriceText->SetColorAndOpacity(Color);
	}
}
