#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "Components/HorizontalBox.h"
#include "GameplayTagContainer.h"
#include "W_StatusEffectBar.generated.h"

class UW_Buff;

UCLASS()
class SLF_5_7_API UW_StatusEffectBar : public UW_UserWidget_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UHorizontalBox> BuffsContainer;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UHorizontalBox> DebuffsContainer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	TSubclassOf<UW_Buff> BuffWidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = "State")
	TMap<FGameplayTag, UW_Buff*> ActiveBuffWidgets;

	UFUNCTION(BlueprintCallable, Category = "StatusEffects")
	void AddStatusEffect(FGameplayTag EffectTag, UTexture2D* Icon, int32 StackCount, float Duration, bool bIsDebuff);

	UFUNCTION(BlueprintCallable, Category = "StatusEffects")
	void UpdateStatusEffect(FGameplayTag EffectTag, int32 StackCount, float Duration);

	UFUNCTION(BlueprintCallable, Category = "StatusEffects")
	void RemoveStatusEffect(FGameplayTag EffectTag);

	UFUNCTION(BlueprintCallable, Category = "StatusEffects")
	void ClearAllEffects();
};
