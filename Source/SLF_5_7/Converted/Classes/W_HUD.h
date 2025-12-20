#pragma once

#include "CoreMinimal.h"
#include "Classes/W_UserWidget_Base.h"
#include "Enums/E_FadeTypes.h"
#include "W_HUD.generated.h"

class UPDA_Vendor;
class UAC_AI_InteractionManager;

UCLASS()
class SLF_5_7_API UW_HUD : public UW_UserWidget_Base
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "HUD")
    void StartFade(E_FadeTypes FadeType, float PlayRate);

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "HUD|Dialog")
    void Event_SetupDialog(const FText& DialogText);

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "HUD|Dialog")
    void Event_FinishDialog();

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "HUD|NPC")
    void Event_SetupNpcWindow(const FText& NpcName, UPDA_Vendor* VendorAsset, UAC_AI_InteractionManager* InteractionManager);
};
