#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PDA_Vendor.generated.h"

class UPDA_Item;

USTRUCT(BlueprintType)
struct SLF_5_7_API FVendorItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UPDA_Item> Item;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Stock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Price;

	FVendorItem()
		: Item(nullptr)
		, Stock(-1)
		, Price(0)
	{}

	bool operator==(const FVendorItem& Other) const
	{
		return Item == Other.Item;
	}

	friend uint32 GetTypeHash(const FVendorItem& VendorItem)
	{
		return GetTypeHash(VendorItem.Item);
	}
};

UCLASS(BlueprintType)
class SLF_5_7_API UPDA_Vendor : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPDA_Vendor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vendor")
	TArray<FVendorItem> Items;

	UFUNCTION(BlueprintCallable, Category = "Vendor")
	void ReduceItemStock(UPDA_Item* Item, int32 Delta);

	UFUNCTION(BlueprintCallable, Category = "Vendor")
	void IncreaseItemStock(UPDA_Item* Item, int32 Delta);

	UFUNCTION(BlueprintPure, Category = "Vendor")
	int32 GetItemStock(UPDA_Item* Item) const;

	UFUNCTION(BlueprintPure, Category = "Vendor")
	int32 GetItemPrice(UPDA_Item* Item) const;
};
