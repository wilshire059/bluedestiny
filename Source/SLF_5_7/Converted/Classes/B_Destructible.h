#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "Components/BillboardComponent.h"
#include "B_Destructible.generated.h"

UCLASS(Blueprintable)
class SLF_5_7_API AB_Destructible : public AActor
{
	GENERATED_BODY()
	
public:	
	AB_Destructible();

protected:
	virtual void BeginPlay() override;

public:	
    // The geometry collection mesh component - set RestCollection on this component directly
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UGeometryCollectionComponent> DestructibleMesh;

    // Billboard for editor visibility
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UBillboardComponent> Billboard;

    // Sound to play when destroyed
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSoftObjectPtr<USoundBase> DestructionSound;

    UFUNCTION()
    void OnChaosBreakEvent(const FChaosBreakEvent& BreakEvent);

private:
    bool bSoundPlayed = false;
};
