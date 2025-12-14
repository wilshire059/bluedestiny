#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "B_DeathTrigger.generated.h"

class UBoxComponent;
class UBillboardComponent;

UCLASS()
class SLF_5_7_API AB_DeathTrigger : public AActor
{
    GENERATED_BODY()
    
public:    
    AB_DeathTrigger();

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
    // Configurable properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TArray<FName> RelevantActorTags;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    float DamageAmount;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UBoxComponent> DeathTriggerBox;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UBillboardComponent> Billboard;
};
