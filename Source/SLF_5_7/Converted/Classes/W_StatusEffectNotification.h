#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "W_StatusEffectNotification.generated.h"

UCLASS()
class SLF_5_7_API UW_StatusEffectNotification : public UW_UserWidget_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> EffectIcon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> EffectNameText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	float DisplayDuration = 3.0f;

	UFUNCTION(BlueprintCallable, Category = "StatusEffect")
	void ShowNotification(UTexture2D* Icon, FText EffectName);

protected:
	FTimerHandle HideTimerHandle;

	UFUNCTION()
	void HideNotification();
};
