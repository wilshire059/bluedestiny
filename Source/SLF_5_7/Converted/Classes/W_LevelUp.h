#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "GameplayTagContainer.h"
#include "Components/Image.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "Components/BackgroundBlur.h"
#include "Components/Button.h"
#include "W_LevelUp.generated.h"

class UW_StatBlock_LevelUp;
class UW_LevelCurrencyBlock_LevelUp;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelUpConfirmed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelUpCancelled);

UCLASS()
class SLF_5_7_API UW_LevelUp : public UW_UserWidget_Base
{
	GENERATED_BODY()

public:
	// ==================== Input Icons ====================
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> BackInputIcon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> OkInputIcon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> ScrollLeftInputIcon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> ScrollRightInputIcon;

	// ==================== Layout Containers ====================
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UHorizontalBox> ButtonsBox;

	// ==================== Background/Blur ====================
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UBackgroundBlur> MainBlur;

	// ==================== Decorative Images ====================
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> Image;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> Image_1;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> Image_2;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> Image_3;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> Image_4;

	// ==================== Text Widgets ====================
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemNameText;

	// ==================== Buttons ====================
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> ConfirmButton;

	// ==================== Stat Block Widgets ====================
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UW_StatBlock_LevelUp> AttackStats;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UW_StatBlock_LevelUp> MiscStats;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UW_StatBlock_LevelUp> NegationStats;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UW_StatBlock_LevelUp> PrimaryAttributes;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UW_StatBlock_LevelUp> ResistanceStats;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UW_StatBlock_LevelUp> SecondaryStats;

	// ==================== Level/Currency Block ====================
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UW_LevelCurrencyBlock_LevelUp> LevelAndCurrencyBlock;

	// ==================== Events ====================
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnLevelUpConfirmed OnLevelUpConfirmed;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnLevelUpCancelled OnLevelUpCancelled;

	// ==================== State ====================
	UPROPERTY(BlueprintReadWrite, Category = "State")
	TMap<FGameplayTag, int32> PendingStatUpgrades;

	// ==================== Functions ====================
	UFUNCTION(BlueprintCallable, Category = "LevelUp")
	void AddStatUpgrade(FGameplayTag StatTag);

	UFUNCTION(BlueprintCallable, Category = "LevelUp")
	void RemoveStatUpgrade(FGameplayTag StatTag);

	UFUNCTION(BlueprintCallable, Category = "LevelUp")
	void ConfirmLevelUp();

	UFUNCTION(BlueprintCallable, Category = "LevelUp")
	void CancelLevelUp();

	UFUNCTION(BlueprintCallable, Category = "LevelUp")
	int64 CalculateTotalCost() const;

	UFUNCTION(BlueprintCallable, Category = "LevelUp")
	int32 CalculateNewLevel() const;

protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "LevelUp")
	void OnStatUpgradesChanged();
};
