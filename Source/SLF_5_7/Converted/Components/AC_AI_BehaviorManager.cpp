#include "AC_AI_BehaviorManager.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Interfaces/BPI_AIC.h"
#include "StructUtils/InstancedStruct.h"

UAC_AI_BehaviorManager::UAC_AI_BehaviorManager()
{
    PrimaryComponentTick.bCanEverTick = true;
    CurrentState = E_AI_States::Idle;
    MaxChaseDistanceThreshold = 1500.0;
    MinChaseDistanceThreshold = 300.0;
}

void UAC_AI_BehaviorManager::BeginPlay()
{
    Super::BeginPlay();

    // Check if Behavior is valid, then initialize
    if (Behavior)
    {
        AActor* Owner = GetOwner();
        if (AAIController* AIC = UAIBlueprintHelperLibrary::GetAIController(Owner))
        {
            // Initialize Behavior through Interface
            if (AIC->Implements<UBPI_AIC>())
            {
                IBPI_AIC::Execute_InitializeBehavior(AIC, Behavior);
            }
        }

        // Check if PatrolPath is valid
        if (PatrolPath)
        {
            // Make instanced struct with patrol path info
            FAiPatrolPathInfo PatrolInfo;
            PatrolInfo.PatrolPath = PatrolPath;
            FInstancedStruct InstancedPatrolInfo = FInstancedStruct::Make(PatrolInfo);

            // Set state to Patrol (NewEnumerator0 = Idle, so patrol might be different)
            SetState(CurrentState, InstancedPatrolInfo);
        }
        else
        {
            // No patrol path - set state to Idle
            SetState(E_AI_States::Idle, FInstancedStruct());
        }

        // Set ChaseDistance key on blackboard directly
        if (UBlackboardComponent* BB = GetBlackboard())
        {
            BB->SetValueAsFloat(FName("ChaseDistance"), static_cast<float>(MaxChaseDistanceThreshold));
        }
    }
}

void UAC_AI_BehaviorManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UAC_AI_BehaviorManager::InitializeBehavior()
{
    // This function is called to initialize the behavior
    // The actual initialization happens in BeginPlay when Behavior is set
    if (Behavior)
    {
        if (AAIController* AIC = UAIBlueprintHelperLibrary::GetAIController(GetOwner()))
        {
            if (AIC->Implements<UBPI_AIC>())
            {
                IBPI_AIC::Execute_InitializeBehavior(AIC, Behavior);
            }
        }
    }
}

void UAC_AI_BehaviorManager::SetState(E_AI_States NewState, const FInstancedStruct& Data)
{
    E_AI_States OldState = CurrentState;
    CurrentState = NewState;

    // Broadcast state change
    OnStateChanged.Broadcast(CurrentState, OldState);

    // Update Blackboard state key
    if (UBlackboardComponent* BB = GetBlackboard())
    {
        BB->SetValueAsEnum(FName("State"), static_cast<uint8>(CurrentState));
    }
}

void UAC_AI_BehaviorManager::SetKeyValue(FName KeyName, const FInstancedStruct& Data)
{
    UBlackboardComponent* BB = GetBlackboard();
    if (!BB || !Data.IsValid())
    {
        return;
    }

    const UScriptStruct* ScriptStruct = Data.GetScriptStruct();
    if (!ScriptStruct)
    {
        return;
    }

    FString StructName = ScriptStruct->GetName();
    const uint8* Memory = Data.GetMemory();

    // Handle known struct wrappers by name (used by Blueprint FInstancedStruct pattern)
    if (StructName == TEXT("FFloat") || StructName == TEXT("Float"))
    {
        // FFloat wraps a double
        const double* FloatValue = reinterpret_cast<const double*>(Memory);
        BB->SetValueAsFloat(KeyName, static_cast<float>(*FloatValue));
    }
    else if (StructName == TEXT("FBool") || StructName == TEXT("Bool"))
    {
        const bool* BoolValue = reinterpret_cast<const bool*>(Memory);
        BB->SetValueAsBool(KeyName, *BoolValue);
    }
    else if (StructName == TEXT("FInt") || StructName == TEXT("Int"))
    {
        const int32* IntValue = reinterpret_cast<const int32*>(Memory);
        BB->SetValueAsInt(KeyName, *IntValue);
    }
    else if (StructName == TEXT("FEnumByte") || StructName == TEXT("EnumByte"))
    {
        const uint8* EnumValue = reinterpret_cast<const uint8*>(Memory);
        BB->SetValueAsEnum(KeyName, *EnumValue);
    }
    else if (StructName == TEXT("FName") || StructName == TEXT("Name"))
    {
        const FName* NameValue = reinterpret_cast<const FName*>(Memory);
        BB->SetValueAsName(KeyName, *NameValue);
    }
    else if (StructName == TEXT("FString") || StructName == TEXT("String"))
    {
        const FString* StringValue = reinterpret_cast<const FString*>(Memory);
        BB->SetValueAsString(KeyName, *StringValue);
    }
    else if (StructName == TEXT("FVector") || StructName == TEXT("Vector"))
    {
        const FVector* VectorValue = reinterpret_cast<const FVector*>(Memory);
        BB->SetValueAsVector(KeyName, *VectorValue);
    }
    else if (StructName == TEXT("FRotator") || StructName == TEXT("Rotator"))
    {
        const FRotator* RotatorValue = reinterpret_cast<const FRotator*>(Memory);
        BB->SetValueAsRotator(KeyName, *RotatorValue);
    }
    else if (StructName == TEXT("FObject") || StructName == TEXT("Object"))
    {
        UObject* const* ObjectValue = reinterpret_cast<UObject* const*>(Memory);
        BB->SetValueAsObject(KeyName, *ObjectValue);
    }
    else if (StructName == TEXT("FClass") || StructName == TEXT("Class"))
    {
        const TSubclassOf<UObject>* ClassValue = reinterpret_cast<const TSubclassOf<UObject>*>(Memory);
        BB->SetValueAsClass(KeyName, *ClassValue);
    }
    else if (StructName == TEXT("FAiPatrolPathInfo") || StructName == TEXT("AiPatrolPathInfo"))
    {
        const FAiPatrolPathInfo* PatrolInfo = reinterpret_cast<const FAiPatrolPathInfo*>(Memory);
        BB->SetValueAsObject(KeyName, PatrolInfo->PatrolPath);
    }
    else if (StructName == TEXT("FAiSenseLocationInfo") || StructName == TEXT("AiSenseLocationInfo"))
    {
        // This contains a SenseLocation (FVector)
        const FVector* LocationValue = reinterpret_cast<const FVector*>(Memory);
        BB->SetValueAsVector(KeyName, *LocationValue);
    }
    else if (StructName == TEXT("FAiSenseTargetInfo") || StructName == TEXT("AiSenseTargetInfo"))
    {
        // This contains a SensedTarget (AActor*)
        AActor* const* ActorValue = reinterpret_cast<AActor* const*>(Memory);
        BB->SetValueAsObject(KeyName, *ActorValue);
    }
}

UBlackboardComponent* UAC_AI_BehaviorManager::GetBlackboard() const
{
    if (AAIController* AIC = UAIBlueprintHelperLibrary::GetAIController(GetOwner()))
    {
        return AIC->GetBlackboardComponent();
    }
    return nullptr;
}

void UAC_AI_BehaviorManager::SetPatrolPath(AB_PatrolPath* NewPatrolPath)
{
    PatrolPath = NewPatrolPath;
}

void UAC_AI_BehaviorManager::SetTarget(AActor* NewTarget)
{
    Target = NewTarget;

    // Also set on blackboard if available
    if (UBlackboardComponent* BB = GetBlackboard())
    {
        BB->SetValueAsObject(FName("Target"), NewTarget);
    }
}
