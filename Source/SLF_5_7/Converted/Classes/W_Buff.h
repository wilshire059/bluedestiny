#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "GameplayTagContainer.h"
#include "W_Buff.generated.h"

UCLASS()
class SLF_5_7_API UW_Buff : public UW_UserWidget_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> BuffIcon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> StackCountText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> DurationText;

	UPROPERTY(BlueprintReadWrite, Category = "State")
	FGameplayTag BuffTag;

	UFUNCTION(BlueprintCallable, Category = "Buff")
	void SetupBuff(FGameplayTag InBuffTag, UTexture2D* Icon, int32 StackCount, float Duration);

	UFUNCTION(BlueprintCallable, Category = "Buff")
	void UpdateStackCount(int32 StackCount);

	UFUNCTION(BlueprintCallable, Category = "Buff")
	void UpdateDuration(float RemainingDuration);
};
