#pragma once

#include "CoreMinimal.h"
#include "W_NPC_Window.h"
#include "Structs/FInventoryItem.h"
#include "Components/ScrollBox.h"
#include "W_NPC_Window_Vendor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnVendorItemSelected, int32, ItemIndex, bool, bIsBuying);

UCLASS()
class SLF_5_7_API UW_NPC_Window_Vendor : public UW_NPC_Window
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UScrollBox> VendorItemsContainer;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UScrollBox> PlayerItemsContainer;

	UPROPERTY(BlueprintAssignable, Category = "Vendor")
	FOnVendorItemSelected OnVendorItemSelected;

	UFUNCTION(BlueprintCallable, Category = "Vendor")
	void SetupVendorInventory(const TArray<FInventoryItem>& VendorItems);

	UFUNCTION(BlueprintCallable, Category = "Vendor")
	void SetupPlayerInventory(const TArray<FInventoryItem>& PlayerItems);

	UFUNCTION(BlueprintCallable, Category = "Vendor")
	void BuyItem(int32 ItemIndex);

	UFUNCTION(BlueprintCallable, Category = "Vendor")
	void SellItem(int32 ItemIndex);

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Vendor")
	void OnSetupVendorItems(const TArray<FInventoryItem>& Items);

	UFUNCTION(BlueprintImplementableEvent, Category = "Vendor")
	void OnSetupPlayerItems(const TArray<FInventoryItem>& Items);
};
