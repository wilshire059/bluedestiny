#include "W_Inventory_ActionButton.h"

UW_Inventory_ActionButton::UW_Inventory_ActionButton(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set default values from Blueprint
	ActionText = FText::FromString("Action");
	Color = FLinearColor(0.129412f, 0.113725f, 0.094118f, 0.949020f);
	SelectedColor = FLinearColor(0.376471f, 0.325490f, 0.270588f, 0.950000f);
	bSelected = false;
}

void UW_Inventory_ActionButton::NativePreConstruct()
{
	Super::NativePreConstruct();

	// Set button color during PreConstruct
	if (Btn)
	{
		Btn->SetBrushColor(Color);
	}

	// Set text during PreConstruct
	if (Txt)
	{
		Txt->SetText(ActionText);
	}
}

void UW_Inventory_ActionButton::NativeConstruct()
{
	Super::NativeConstruct();

	// Bind button events
	if (UseButton)
	{
		UseButton->OnPressed.AddDynamic(this, &UW_Inventory_ActionButton::OnUseButtonPressed);
		UseButton->OnHovered.AddDynamic(this, &UW_Inventory_ActionButton::OnUseButtonHovered);
	}
}

void UW_Inventory_ActionButton::OnUseButtonPressed()
{
	// Broadcast the pressed event
	OnActionButtonPressed.Broadcast();

	// Call the Blueprint implementable event
	ActionPressed();
}

void UW_Inventory_ActionButton::OnUseButtonHovered()
{
	// Set this button as selected when hovered
	SetActionButtonSelected(true);
}

void UW_Inventory_ActionButton::SetActionButtonSelected(bool bNewSelected)
{
	// Update the selected state
	bSelected = bNewSelected;

	// Change the button color based on selected state
	if (Btn)
	{
		if (bNewSelected)
		{
			Btn->SetBrushColor(SelectedColor);
			// Notify listeners that this button was selected
			OnActionButtonSelected.Broadcast(this);
		}
		else
		{
			Btn->SetBrushColor(Color);
		}
	}
}
