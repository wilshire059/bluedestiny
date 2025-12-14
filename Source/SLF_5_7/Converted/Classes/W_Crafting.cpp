#include "W_Crafting.h"

void UW_Crafting::SetupCraftingMenu(const TArray<FCraftingInfo>& Recipes)
{
	OnSetupRecipes(Recipes);
}

void UW_Crafting::SelectRecipe(int32 RecipeIndex)
{
	SelectedRecipeIndex = RecipeIndex;
	OnCraftingRecipeSelected.Broadcast(RecipeIndex);
}

void UW_Crafting::CraftSelectedItem()
{
	// Craft logic - implemented in Blueprint
}

void UW_Crafting::CloseCraftingMenu()
{
	RemoveFromParent();
}
