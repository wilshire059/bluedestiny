#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "Enums/E_Progress.h"
#include "AC_ProgressManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnProgressUpdated, FGameplayTag, ID, E_Progress, NewState);

UCLASS( ClassGroup=(Custom), Blueprintable, meta=(BlueprintSpawnableComponent) )
class SLF_5_7_API UAC_ProgressManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAC_ProgressManager();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Progress")
    TMap<FGameplayTag, E_Progress> ProgressState;

    // Default configuration: ID -> Initial State
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Progress")
    TMap<FGameplayTag, E_Progress> DefaultsToProgress;

    UPROPERTY(BlueprintAssignable, Category = "Progress")
    FOnProgressUpdated OnProgressUpdated;

    UFUNCTION(BlueprintCallable, Category = "Progress")
    void SetProgress(FGameplayTag ID, E_Progress State);

    UFUNCTION(BlueprintCallable, Category = "Progress")
    E_Progress GetProgress(FGameplayTag ID) const;

protected:
	virtual void BeginPlay() override;
};
