#include "AC_InteractionManager.h"

UAC_InteractionManager::UAC_InteractionManager()
{
	PrimaryComponentTick.bCanEverTick = true;
	InteractionRange = 200.0f;
}

void UAC_InteractionManager::BeginPlay()
{
	Super::BeginPlay();
}

void UAC_InteractionManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UAC_InteractionManager::TryInteract()
{
	if (CurrentInteractable)
	{
		// Call interaction interface on current interactable
		// Implementation depends on BPI_Interactable interface
	}
}

void UAC_InteractionManager::UpdateInteractable(AActor* NewInteractable)
{
	if (CurrentInteractable != NewInteractable)
	{
		if (CurrentInteractable && !NewInteractable)
		{
			OnInteractableLost.Broadcast();
		}

		CurrentInteractable = NewInteractable;

		if (NewInteractable)
		{
			OnInteractableDetected.Broadcast(NewInteractable);
		}
	}
}

bool UAC_InteractionManager::HasInteractable() const
{
	return CurrentInteractable != nullptr;
}
