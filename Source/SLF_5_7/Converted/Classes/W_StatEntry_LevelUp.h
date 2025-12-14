#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "GameplayTagContainer.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "W_StatEntry_LevelUp.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStatUpgradeRequested, FGameplayTag, StatTag);

UCLASS()
class SLF_5_7_API UW_StatEntry_LevelUp : public UW_UserWidget_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> StatNameText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> CurrentValueText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> NewValueText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<UButton> UpgradeButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FGameplayTag StatTag;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnStatUpgradeRequested OnStatUpgradeRequested;

	UFUNCTION(BlueprintCallable, Category = "LevelUp")
	void SetupEntry(FGameplayTag InStatTag, int32 CurrentValue, int32 NewValue, bool bCanUpgrade);

protected:
	UFUNCTION()
	void HandleUpgradeClicked();
};
