#include "W_Resources.h"

void UW_Resources::NativeConstruct()
{
	Super::NativeConstruct();
	BindToStatManager();
}

void UW_Resources::BindToStatManager()
{
	// Bind to stat manager updates - implemented in Blueprint
}

void UW_Resources::UpdateHealth(float Current, float Max)
{
	float Percent = Max > 0.0f ? Current / Max : 0.0f;

	if (HealthBar)
	{
		HealthBar->SetPercent(Percent);
	}

	if (HealthText)
	{
		HealthText->SetText(FText::Format(NSLOCTEXT("Resources", "Health", "{0}/{1}"), FMath::FloorToInt(Current), FMath::FloorToInt(Max)));
	}
}

void UW_Resources::UpdateFP(float Current, float Max)
{
	float Percent = Max > 0.0f ? Current / Max : 0.0f;

	if (FPBar)
	{
		FPBar->SetPercent(Percent);
	}

	if (FPText)
	{
		FPText->SetText(FText::Format(NSLOCTEXT("Resources", "FP", "{0}/{1}"), FMath::FloorToInt(Current), FMath::FloorToInt(Max)));
	}
}

void UW_Resources::UpdateStamina(float Current, float Max)
{
	float Percent = Max > 0.0f ? Current / Max : 0.0f;

	if (StaminaBar)
	{
		StaminaBar->SetPercent(Percent);
	}

	if (StaminaText)
	{
		StaminaText->SetText(FText::Format(NSLOCTEXT("Resources", "Stamina", "{0}/{1}"), FMath::FloorToInt(Current), FMath::FloorToInt(Max)));
	}
}
