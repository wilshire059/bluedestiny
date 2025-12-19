#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "Enums/E_Progress.h"
#include "AC_ProgressManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnProgressUpdated, FGameplayTag, ID, E_Progress, NewState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnProgressSaveRequested, FGameplayTag, SaveDataTag);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayTimeUpdated, FTimespan, NewTime);

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

    UPROPERTY(BlueprintAssignable, Category = "Progress")
    FOnProgressSaveRequested OnSaveRequested;

    UPROPERTY(BlueprintAssignable, Category = "Progress")
    FOnPlayTimeUpdated OnPlayTimeUpdated;

    UFUNCTION(BlueprintCallable, Category = "Progress")
    void SetProgress(FGameplayTag ID, E_Progress State);

    UFUNCTION(BlueprintCallable, Category = "Progress")
    E_Progress GetProgress(FGameplayTag ID) const;

protected:
	virtual void BeginPlay() override;
};
