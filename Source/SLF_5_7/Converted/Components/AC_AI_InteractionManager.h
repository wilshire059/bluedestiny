#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DataAssets/PDA_Dialog.h" // Assuming this exists or will handle gracefully
#include "AC_ProgressManager.h"
#include "Engine/DataTable.h"
#include "AC_AI_InteractionManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDialogStarted, UDataTable*, DialogTable);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SLF_5_7_API UAC_AI_InteractionManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAC_AI_InteractionManager();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
    TObjectPtr<UPDA_Dialog> DialogAsset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
    TObjectPtr<UAC_ProgressManager> ProgressManager;

    UPROPERTY(BlueprintAssignable, Category = "Interaction")
    FOnDialogStarted OnDialogStarted;

    UFUNCTION(BlueprintCallable, Category = "Interaction")
    void BeginDialog();

protected:
	virtual void BeginPlay() override;
};
