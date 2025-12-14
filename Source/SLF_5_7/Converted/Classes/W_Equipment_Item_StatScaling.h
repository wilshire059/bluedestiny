#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "GameplayTagContainer.h"
#include "Enums/E_StatScaling.h"
#include "Components/VerticalBox.h"
#include "W_Equipment_Item_StatScaling.generated.h"

UCLASS()
class SLF_5_7_API UW_Equipment_Item_StatScaling : public UW_UserWidget_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UVerticalBox> StatScalingContainer;

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void SetupStatScaling(const TMap<FGameplayTag, E_StatScaling>& StatScaling);

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Equipment")
	void OnSetupStatScaling(const TMap<FGameplayTag, E_StatScaling>& Scaling);
};
