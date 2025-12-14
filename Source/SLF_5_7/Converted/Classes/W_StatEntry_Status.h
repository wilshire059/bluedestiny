#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "GameplayTagContainer.h"
#include "Components/TextBlock.h"
#include "W_StatEntry_Status.generated.h"

UCLASS()
class SLF_5_7_API UW_StatEntry_Status : public UW_UserWidget_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> StatNameText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> StatValueText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FGameplayTag StatTag;

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void SetupStatusEntry(FGameplayTag InStatTag, FText StatName, int32 StatValue);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void UpdateStatValue(int32 NewValue);
};
