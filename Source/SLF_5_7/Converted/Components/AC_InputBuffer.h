#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "AC_InputBuffer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInputBufferConsumed, FGameplayTag, Action);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SLF_5_7_API UAC_InputBuffer : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAC_InputBuffer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InputBuffer")
    bool bBufferOpen;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InputBuffer")
    FGameplayTag IncomingActionTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InputBuffer")
    FGameplayTagContainer IgnoreNextOfActions;

    UPROPERTY(BlueprintAssignable, Category = "InputBuffer")
    FOnInputBufferConsumed OnInputBufferConsumed;

    UFUNCTION(BlueprintCallable, Category = "InputBuffer")
    void ToggleBuffer(bool bOpen);

    UFUNCTION(BlueprintCallable, Category = "InputBuffer")
    void QueueAction(FGameplayTag ActionTag);

    UFUNCTION(BlueprintCallable, Category = "InputBuffer")
    void ConsumeInputBuffer();
    
    // Internal handler for event-driven logic
    UFUNCTION(BlueprintCallable, Category = "InputBuffer")
    void QueueNext(FGameplayTag ActionTag);
};
