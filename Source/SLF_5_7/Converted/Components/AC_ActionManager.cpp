#include "AC_ActionManager.h"
#include "AC_StatManager.h"
#include "Net/UnrealNetwork.h"
#include "TimerManager.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetMathLibrary.h"
#include "Classes/B_Action.h"
#include "Classes/B_Stat.h"
#include "DataAssets/PDA_Action.h"
#include "Engine/DataTable.h"

UAC_ActionManager::UAC_ActionManager()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);

	MovementDirection = E_Direction::None;
	MovementVector = FVector2D::ZeroVector;
	bIsOnLadder = false;
	MinValue = 0.0;
}

void UAC_ActionManager::BeginPlay()
{
	Super::BeginPlay();

	// Initialize by loading actions
	RecursiveLoadActions();
}

void UAC_ActionManager::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UAC_ActionManager, MovementDirection);
}

// ============================================================
// MOVEMENT DIRECTION FUNCTIONS
// ============================================================

void UAC_ActionManager::SetMoveDir(FVector2D IAMove)
{
	// Store the movement vector
	MovementVector = IAMove;

	// Calculate vector length to check deadzone
	const double Length = IAMove.Size();

	// Deadzone check - if length <= 0.1, don't change direction
	if (Length <= 0.1)
	{
		return;
	}

	// Calculate angle in degrees using atan2(Y, X)
	// This gives us the angle from the positive X axis
	const double Degrees = FMath::RadiansToDegrees(FMath::Atan2(IAMove.Y, IAMove.X));

	// Calculate the direction based on angle
	E_Direction NewDirection = CalculateDirectionFromAngle(Degrees);

	// Only update if direction changed and is not None
	if (NewDirection != MovementDirection && NewDirection != E_Direction::None)
	{
		SRV_SetDirection(NewDirection);
	}
}

E_Direction UAC_ActionManager::CalculateDirectionFromAngle(double Degrees) const
{
	// Normalize angle to -180 to 180 range
	// In UE coordinate system with default input:
	// Forward (W) = Y positive = 90 degrees
	// Right (D) = X positive = 0 degrees
	// Backward (S) = Y negative = -90 degrees
	// Left (A) = X negative = 180/-180 degrees

	// 8-way direction detection using 45-degree sectors (22.5 degree half-width)
	// Each direction occupies a 45-degree arc

	if (Degrees >= 67.5 && Degrees < 112.5)
	{
		return E_Direction::Forward;
	}
	else if (Degrees >= 22.5 && Degrees < 67.5)
	{
		return E_Direction::ForwardRight;
	}
	else if (Degrees >= -22.5 && Degrees < 22.5)
	{
		return E_Direction::Right;
	}
	else if (Degrees >= -67.5 && Degrees < -22.5)
	{
		return E_Direction::BackwardRight;
	}
	else if (Degrees >= -112.5 && Degrees < -67.5)
	{
		return E_Direction::Backward;
	}
	else if (Degrees >= -157.5 && Degrees < -112.5)
	{
		return E_Direction::BackwardLeft;
	}
	else if (Degrees >= 112.5 && Degrees < 157.5)
	{
		return E_Direction::ForwardLeft;
	}
	else // >= 157.5 || < -157.5
	{
		return E_Direction::Left;
	}
}

void UAC_ActionManager::SRV_SetDirection_Implementation(E_Direction Direction)
{
	// Server receives direction change request, broadcast to all clients
	MC_SetDirection(Direction);
}

void UAC_ActionManager::MC_SetDirection_Implementation(E_Direction Direction)
{
	// Set the movement direction on all clients
	MovementDirection = Direction;

	// Broadcast the change
	OnDirectionChanged.Broadcast(MovementDirection);
}

bool UAC_ActionManager::GetIsMoving2D() const
{
	// Return true if movement vector has significant magnitude
	return MovementVector.Size() > 0.1;
}

// ============================================================
// ACTION SYSTEM FUNCTIONS
// ============================================================

void UAC_ActionManager::PerformAction(FGameplayTag ActionTag)
{
	// Check if we're on a ladder - actions may be restricted
	if (bIsOnLadder)
	{
		OnActionPerformed.Broadcast(ActionTag, false);
		return;
	}

	// Find the action in our available actions map
	if (TObjectPtr<UB_Action>* FoundAction = AvailableActions.Find(ActionTag))
	{
		if (*FoundAction)
		{
			// Execute the action
			// The actual execution logic would be in UB_Action
			OnActionPerformed.Broadcast(ActionTag, true);
		}
		else
		{
			OnActionPerformed.Broadcast(ActionTag, false);
		}
	}
	else
	{
		OnActionPerformed.Broadcast(ActionTag, false);
	}
}

void UAC_ActionManager::RecursiveLoadActions()
{
	// Clear caches
	ActionTagsCache.Empty();
	ActionAssetsCache.Empty();
	AvailableActions.Empty();

	// Load actions from the Actions map
	for (const auto& ActionPair : Actions)
	{
		const FGameplayTag& Tag = ActionPair.Key;
		const TSoftClassPtr<UB_Action>& ActionClass = ActionPair.Value;

		ActionTagsCache.Add(Tag);

		// Load the action class if valid
		if (!ActionClass.IsNull())
		{
			UClass* LoadedClass = ActionClass.LoadSynchronous();
			if (LoadedClass)
			{
				UB_Action* NewAction = NewObject<UB_Action>(this, LoadedClass);
				if (NewAction)
				{
					AvailableActions.Add(Tag, NewAction);
				}
			}
		}
	}

	// Handle override table if present
	if (OverrideTable)
	{
		// Process data table overrides
		// Implementation depends on the specific row structure of the data table
	}
}

// ============================================================
// STAT HELPER FUNCTIONS
// ============================================================

UAC_StatManager* UAC_ActionManager::GetStatManager() const
{
	if (AActor* Owner = GetOwner())
	{
		return Owner->FindComponentByClass<UAC_StatManager>();
	}
	return nullptr;
}

double UAC_ActionManager::GetStat(FGameplayTag StatTag) const
{
	if (UAC_StatManager* StatManager = GetStatManager())
	{
		if (UB_Stat* Stat = StatManager->GetStat(StatTag))
		{
			return static_cast<double>(Stat->CurrentValue);
		}
	}
	return 0.0;
}

void UAC_ActionManager::AdjustStat(FGameplayTag StatTag, double Change, E_ValueType ValueType)
{
	if (UAC_StatManager* StatManager = GetStatManager())
	{
		// Use StatManager's ModifyStat which handles the value type
		StatManager->ModifyStat(StatTag, static_cast<float>(Change), ValueType);
	}
}

void UAC_ActionManager::AdjustValue(FGameplayTag StatTag, double Change, E_ValueType ValueType)
{
	// Round the change value
	int32 RoundedChange = FMath::RoundToInt(Change);

	if (UAC_StatManager* StatManager = GetStatManager())
	{
		if (UB_Stat* Stat = StatManager->GetStat(StatTag))
		{
			// Apply the adjustment based on type
			switch (ValueType)
			{
			case E_ValueType::Current:
				{
					float NewValue = FMath::Max(static_cast<float>(MinValue), Stat->CurrentValue + static_cast<float>(Change));
					Stat->SetCurrentValue(NewValue);
				}
				break;
			case E_ValueType::Max:
				{
					float NewValue = FMath::Max(static_cast<float>(MinValue), Stat->MaxValue + static_cast<float>(Change));
					Stat->MaxValue = NewValue;
				}
				break;
			case E_ValueType::Base:
				{
					float NewValue = FMath::Max(static_cast<float>(MinValue), Stat->BaseValue + static_cast<float>(Change));
					Stat->BaseValue = NewValue;
				}
				break;
			default:
				break;
			}
		}
	}
}

bool UAC_ActionManager::IsStatMoreThan(FGameplayTag StatTag, double CompareValue) const
{
	double StatValue = GetStat(StatTag);
	return StatValue > CompareValue;
}

// ============================================================
// STAMINA FUNCTIONS
// ============================================================

void UAC_ActionManager::StartStaminaLoss()
{
	// Start a timer to reduce stamina while sprinting
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().SetTimer(
			StaminaLossTimer,
			this,
			&UAC_ActionManager::ReduceStamina,
			0.1f, // Reduce every 0.1 seconds
			true  // Looping
		);
	}
}

void UAC_ActionManager::ReduceStamina()
{
	// Get stamina stat tag (would need to be defined or passed in)
	FGameplayTag StaminaTag = FGameplayTag::RequestGameplayTag(FName("SoulslikeFramework.Stat.Primary.Stamina"), false);

	if (StaminaTag.IsValid())
	{
		// Reduce stamina by a fixed amount per tick
		AdjustStat(StaminaTag, -5.0, E_ValueType::Current);

		// Check if stamina depleted, stop sprinting if so
		if (!IsStatMoreThan(StaminaTag, 0.0))
		{
			StopStaminaLoss();
		}
	}
}

void UAC_ActionManager::StopStaminaLoss()
{
	// Clear the stamina loss timer
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(StaminaLossTimer);
	}

	// Start stamina regeneration
	StartStaminaRegen();
}

void UAC_ActionManager::StartStaminaRegen()
{
	// Stamina regeneration would be handled by the StatManager's regen system
	// This function signals that the character has stopped sprinting
	// and stamina should begin regenerating

	// Implementation depends on how the stat regen system works
}

// ============================================================
// UTILITY FUNCTIONS
// ============================================================

FString UAC_ActionManager::ParseOutTagName(FGameplayTag Tag) const
{
	// Get the full tag string
	FString TagString = Tag.ToString();

	// Find the last period to extract the final segment
	int32 LastPeriodIndex;
	if (TagString.FindLastChar('.', LastPeriodIndex))
	{
		return TagString.RightChop(LastPeriodIndex + 1);
	}

	// If no period found, return the whole string
	return TagString;
}
