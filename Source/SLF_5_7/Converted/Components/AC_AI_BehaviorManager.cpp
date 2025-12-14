#include "AC_AI_BehaviorManager.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Interfaces/BPI_AIC.h"

UAC_AI_BehaviorManager::UAC_AI_BehaviorManager()
{
	PrimaryComponentTick.bCanEverTick = true;
    CurrentState = E_AI_States::Idle;
    MaxChaseDistanceThreshold = 1500.0f;
    MinChaseDistanceThreshold = 300.0f;
}

void UAC_AI_BehaviorManager::BeginPlay()
{
	Super::BeginPlay();

    if (AActor* Owner = GetOwner())
    {
        if (AAIController* AIC = UAIBlueprintHelperLibrary::GetAIController(Owner))
        {
            // Initialize Behavior through Interface
            if (AIC->Implements<UBPI_AIC>())
            {
               // IBPI_AIC::Execute_InitializeBehavior(AIC, Owner, nullptr); // Requires specific behavior tree asset
            }
        }
    }
}

void UAC_AI_BehaviorManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UAC_AI_BehaviorManager::SetState(E_AI_States NewState, const FInstancedStruct& Data)
{
    if (CurrentState != NewState)
    {
        E_AI_States OldState = CurrentState;
        CurrentState = NewState;
        OnStateChanged.Broadcast(CurrentState, OldState);

        // Logic to update Blackboard or Behavior Tree would go here
        if (AAIController* AIC = UAIBlueprintHelperLibrary::GetAIController(GetOwner()))
        {
            if (UBlackboardComponent* BB = AIC->GetBlackboardComponent())
            {
                 BB->SetValueAsEnum(FName("State"), (uint8)CurrentState);
            }
        }
    }
}

void UAC_AI_BehaviorManager::SetKeyValue(FName KeyName, const FInstancedStruct& Data)
{
    // Stub implementation for setting blackboard keys based on instanced struct data
    // Would require casting data to specific types
}
