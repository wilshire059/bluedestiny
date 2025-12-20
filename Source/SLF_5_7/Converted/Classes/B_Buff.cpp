#include "B_Buff.h"
#include "DataAssets/PDA_Buff.h"
#include "Components/AC_StatManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameplayTagsManager.h"
#include "Curves/CurveFloat.h"

UB_Buff::UB_Buff()
{
	Rank = 1;
	RemainingDuration = 0.0f;
}

void UB_Buff::OnGranted_Implementation()
{
	// Event OnGranted logic from Blueprint:
	// Get BuffData -> Get BuffTag -> Get Tag Name -> Format "Buff "{tag}" granted." -> Print Text

	if (BuffData)
	{
		FGameplayTag BuffTag = BuffData->BuffTag;
		FName TagName = BuffTag.GetTagName();

		// Format text: "Buff "{tag}" granted."
		FText FormattedText = FText::Format(
			FText::FromString(TEXT("Buff \"{0}\" granted.")),
			FText::FromName(TagName)
		);

		// Print to screen and log with purple color
		UKismetSystemLibrary::PrintText(
			this,
			FormattedText,
			true,  // Print to Screen
			true,  // Print to Log
			FLinearColor(0.405308f, 0.255518f, 1.0f, 1.0f),  // Purple color
			2.0f   // Duration
		);
	}
}

void UB_Buff::OnRemoved_Implementation()
{
	// Event OnRemoved logic from Blueprint:
	// Get BuffData -> Get BuffTag -> Get Tag Name -> Format "Buff "{tag}" removed." -> Print Text

	if (BuffData)
	{
		FGameplayTag BuffTag = BuffData->BuffTag;
		FName TagName = BuffTag.GetTagName();

		// Format text: "Buff "{tag}" removed."
		FText FormattedText = FText::Format(
			FText::FromString(TEXT("Buff \"{0}\" removed.")),
			FText::FromName(TagName)
		);

		// Print to screen and log with blue color
		UKismetSystemLibrary::PrintText(
			this,
			FormattedText,
			true,  // Print to Screen
			true,  // Print to Log
			FLinearColor(0.201200f, 0.0f, 1.0f, 1.0f),  // Blue color
			2.0f   // Duration
		);
	}
}

void UB_Buff::OnTick_Implementation(float DeltaTime)
{
	RemainingDuration -= DeltaTime;
}

float UB_Buff::GetMultiplierForCurrentRank() const
{
	// GetMultiplierForCurrentRank logic from Blueprint:
	// 1. Get RankMultiplierCurve from BuffData
	// 2. Check if valid
	// 3. Convert Rank (int) to double/float
	// 4. Get float value from curve at Rank
	// 5. Return the value

	if (BuffData && BuffData->RankMultiplierCurve.IsValid())
	{
		UCurveFloat* Curve = BuffData->RankMultiplierCurve.Get();
		if (Curve)
		{
			float RankAsFloat = static_cast<float>(Rank);
			return Curve->GetFloatValue(RankAsFloat);
		}
	}

	return 1.0f;  // Default multiplier if no curve
}

UAC_StatManager* UB_Buff::GetOwnerStatManager() const
{
	// GetOwnerStatManager logic from Blueprint:
	// 1. Check if OwnerActor is valid
	// 2. Get AC_StatManager component from OwnerActor
	// 3. Check if component is valid
	// 4. Return the component

	if (OwnerActor)
	{
		UAC_StatManager* StatManager = OwnerActor->FindComponentByClass<UAC_StatManager>();
		if (StatManager)
		{
			return StatManager;
		}
	}

	return nullptr;
}
