#include "AC_LadderManager.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UAC_LadderManager::UAC_LadderManager()
{
	PrimaryComponentTick.bCanEverTick = true;
    bIsClimbing = false;
    ClimbAnimState = E_LadderClimbState::None;
}

void UAC_LadderManager::BeginPlay()
{
	Super::BeginPlay();
    SetComponentTickEnabled(false);
}

void UAC_LadderManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    // Ladder logic (Movement interpolation, animation state updates)
}

void UAC_LadderManager::ToggleClimbing(bool bEnable, const FVector& StartLocation, const FRotator& StartRotation)
{
    bIsClimbing = bEnable;
    SetComponentTickEnabled(bIsClimbing);

    if (ACharacter* Char = Cast<ACharacter>(GetOwner()))
    {
        if (bIsClimbing)
        {
            Char->GetCharacterMovement()->SetMovementMode(MOVE_Flying);
            Char->SetActorLocationAndRotation(StartLocation, StartRotation);
            SetClimbState(E_LadderClimbState::ClimbLoop);
        }
        else
        {
            Char->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
            SetClimbState(E_LadderClimbState::None);
        }
    }
}

void UAC_LadderManager::SetClimbState(E_LadderClimbState NewState)
{
    ClimbAnimState = NewState;
}

void UAC_LadderManager::HandleMoveInput(const FVector2D& InputValue)
{
    if (!bIsClimbing) return;
    
    // Vertical Movement Logic
    if (ACharacter* Char = Cast<ACharacter>(GetOwner()))
    {
        Char->AddMovementInput(FVector::UpVector, InputValue.Y);
    }
}

void UAC_LadderManager::SetIsClimbingDownFromTop(bool bIsDown)
{
    if (bIsDown)
    {
        SetClimbState(E_LadderClimbState::ClimbIntoLadderFromTop);
    }
    else
    {
        // Maybe reset to ClimbLoop or None depending on context, for now just ensuring state is set if entering
    }
}
