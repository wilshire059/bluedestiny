#include "PC_SoulslikeFramework.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "AC_InventoryManager.h"
#include "AC_StatManager.h"
#include "AC_ProgressManager.h"

APC_SoulslikeFramework::APC_SoulslikeFramework()
{
}

void APC_SoulslikeFramework::BeginPlay()
{
	Super::BeginPlay();

	// Setup default input mapping context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (DefaultMappingContext)
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void APC_SoulslikeFramework::SetupInputComponent()
{
	Super::SetupInputComponent();
}

UAC_InventoryManager* APC_SoulslikeFramework::GetInventoryComponent_Implementation()
{
	return InventoryManager;
}

void APC_SoulslikeFramework::StartRespawn_Implementation(double FadeDelay)
{
	// Show "YOU DIED" message
	Execute_SendBigScreenMessage(this, FText::FromString(TEXT("YOU DIED")), nullptr, true, 0.5);

	// Additional respawn logic would go here
}

void APC_SoulslikeFramework::SendBigScreenMessage_Implementation(const FText& Text, UMaterialInterface* GradientMaterial, bool bBackdrop, double PlayRate)
{
	// Implementation would display a large screen message widget
	// This is a stub - actual widget creation deferred to Blueprint child
}

void APC_SoulslikeFramework::SwitchInputContext_Implementation(const TArray<UInputMappingContext*>& ContextsToEnable, const TArray<UInputMappingContext*>& ContextsToDisable)
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// Remove contexts to disable
		for (UInputMappingContext* Context : ContextsToDisable)
		{
			if (Context)
			{
				Subsystem->RemoveMappingContext(Context);
			}
		}

		// Add contexts to enable
		for (UInputMappingContext* Context : ContextsToEnable)
		{
			if (Context)
			{
				Subsystem->AddMappingContext(Context, 0);
			}
		}
	}
}

UAC_ProgressManager* APC_SoulslikeFramework::GetProgressManager_Implementation()
{
	return ProgressManager;
}

APlayerController* APC_SoulslikeFramework::GetSoulslikeController_Implementation()
{
	return this;
}

APawn* APC_SoulslikeFramework::GetPawnFromController_Implementation()
{
	return GetPawn();
}
