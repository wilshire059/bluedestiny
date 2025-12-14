#include "W_CraftingAction.h"

void UW_CraftingAction::NativeConstruct()
{
	Super::NativeConstruct();

	if (CraftButton)
	{
		CraftButton->OnClicked.AddDynamic(this, &UW_CraftingAction::HandleCraftClicked);
	}
}

void UW_CraftingAction::HandleCraftClicked()
{
	OnCraftActionClicked.Broadcast();
}

void UW_CraftingAction::SetCanCraft(bool bCanCraft)
{
	if (CraftButton)
	{
		CraftButton->SetIsEnabled(bCanCraft);
	}
}
