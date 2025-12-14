#include "W_Boss_Healthbar.h"

void UW_Boss_Healthbar::SetupBossHealthbar(AActor* Boss, FText BossName)
{
	TrackedBoss = Boss;

	if (BossNameText)
	{
		BossNameText->SetText(BossName);
	}

	ShowHealthbar();
}

void UW_Boss_Healthbar::UpdateHealth(float CurrentHealth, float MaxHealth)
{
	float HealthPercent = MaxHealth > 0.0f ? CurrentHealth / MaxHealth : 0.0f;

	if (HealthBar)
	{
		HealthBar->SetPercent(HealthPercent);
	}

	// Background bar would interpolate slowly for damage visualization
	// Implemented in Blueprint with tick
}

void UW_Boss_Healthbar::ShowHealthbar()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UW_Boss_Healthbar::HideHealthbar()
{
	SetVisibility(ESlateVisibility::Collapsed);
	TrackedBoss = nullptr;
}
