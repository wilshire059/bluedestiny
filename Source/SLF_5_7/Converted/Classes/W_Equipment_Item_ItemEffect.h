#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "W_Equipment_Item_ItemEffect.generated.h"

UCLASS()
class SLF_5_7_API UW_Equipment_Item_ItemEffect : public UW_UserWidget_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UVerticalBox> EffectsContainer;

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void SetupItemEffects(const TArray<FText>& Effects);

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Equipment")
	void OnSetupItemEffects(const TArray<FText>& Effects);
};
