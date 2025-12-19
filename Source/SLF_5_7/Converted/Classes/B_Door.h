#pragma once

#include "CoreMinimal.h"
#include "B_Interactable.h"
#include "Structs/FDoorLockInfo.h"
#include "PDA_Item.h"  // Verify this include
#include "AC_InventoryManager.h"
#include "AC_EquipmentManager.h"
#include "Components/TimelineComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BillboardComponent.h"
#include "Components/ArrowComponent.h"
#include "Curves/CurveFloat.h" 

#include "B_Door.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDoorOpened);

UCLASS()
class SLF_5_7_API AB_Door : public AB_Interactable
{
    GENERATED_BODY()

public:
    AB_Door();

    // Components
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UStaticMeshComponent> DoorFrame;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UTimelineComponent> DoorTimeline;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UBillboardComponent> MoveTo;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UArrowComponent> OpeningDirection;

    // Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
    FDoorLockInfo LockInfo;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
    TObjectPtr<UCurveFloat> DoorCurve;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnDoorOpened OnDoorOpened;

    // Timeline Track
    FOnTimelineFloat UpdateTimelineFloat;
    FOnTimelineEvent TimelineFinished;

    // Interface Overrides
    virtual void OnInteract_Implementation(AActor* InteractingActor) override;

    // Functions
    UFUNCTION(BlueprintCallable, Category = "Door")
    bool ValidateUnlockRequirements(AActor* PlayerActor);

    UFUNCTION()
    void OpenDoor(float Value);
    
    // Timeline Callbacks
    UFUNCTION()
    void OnTimelineUpdated(float Value);

protected:
    virtual void BeginPlay() override;
    
    FRotator InitialRot;
    FRotator TargetRot;
};
