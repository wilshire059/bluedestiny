#pragma once

#include "CoreMinimal.h"
#include "Classes/W_UserWidget_Base.h"
#include "Enums/E_FadeTypes.h"
#include "W_HUD.generated.h"

UCLASS()
class SLF_5_7_API UW_HUD : public UW_UserWidget_Base
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "HUD")
    void StartFade(E_FadeTypes FadeType, float PlayRate);

    // Add other event listeners as needed, many are likely BP implemented
    // But we can expose common HUD functions here
};
