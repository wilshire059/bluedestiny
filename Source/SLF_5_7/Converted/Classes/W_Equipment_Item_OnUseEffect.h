#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "W_Equipment_Item_OnUseEffect.generated.h"

UCLASS()
class SLF_5_7_API UW_Equipment_Item_OnUseEffect : public UW_UserWidget_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UVerticalBox> OnUseEffectsContainer;

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void SetupOnUseEffects(const TArray<FText>& OnUseEffects);

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Equipment")
	void OnSetupOnUseEffects(const TArray<FText>& OnUseEffects);
};
