#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "W_CraftingAction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCraftActionClicked);

UCLASS()
class SLF_5_7_API UW_CraftingAction : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> CraftButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> CraftButtonText;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnCraftActionClicked OnCraftActionClicked;

	UFUNCTION(BlueprintCallable, Category = "Crafting")
	void SetCanCraft(bool bCanCraft);

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void HandleCraftClicked();
};
