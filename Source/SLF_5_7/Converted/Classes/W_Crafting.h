#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "Components/ScrollBox.h"
#include "Structs/FCraftingInfo.h"
#include "W_Crafting.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCraftingRecipeSelected, int32, RecipeIndex);

UCLASS()
class SLF_5_7_API UW_Crafting : public UW_UserWidget_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UScrollBox> RecipeListContainer;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnCraftingRecipeSelected OnCraftingRecipeSelected;

	UFUNCTION(BlueprintCallable, Category = "Crafting")
	void SetupCraftingMenu(const TArray<FCraftingInfo>& Recipes);

	UFUNCTION(BlueprintCallable, Category = "Crafting")
	void SelectRecipe(int32 RecipeIndex);

	UFUNCTION(BlueprintCallable, Category = "Crafting")
	void CraftSelectedItem();

	UFUNCTION(BlueprintCallable, Category = "Crafting")
	void CloseCraftingMenu();

protected:
	UPROPERTY(BlueprintReadWrite, Category = "State")
	int32 SelectedRecipeIndex = -1;

	UFUNCTION(BlueprintImplementableEvent, Category = "Crafting")
	void OnSetupRecipes(const TArray<FCraftingInfo>& Recipes);
};
