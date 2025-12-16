#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AC_InteractionManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractableDetected, AActor*, Interactable);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractableLost);

UCLASS(ClassGroup=(Custom), Blueprintable, meta=(BlueprintSpawnableComponent))
class SLF_5_7_API UAC_InteractionManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UAC_InteractionManager();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	TObjectPtr<AActor> CurrentInteractable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	float InteractionRange;

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteractableDetected OnInteractableDetected;

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteractableLost OnInteractableLost;

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void TryInteract();

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void UpdateInteractable(AActor* NewInteractable);

	UFUNCTION(BlueprintPure, Category = "Interaction")
	bool HasInteractable() const;

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
