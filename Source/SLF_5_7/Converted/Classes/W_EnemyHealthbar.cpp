#include "W_EnemyHealthbar.h"

void UW_EnemyHealthbar::SetupEnemyHealthbar(AActor* Enemy, FText EnemyName, int32 Level)
{
	TrackedEnemy = Enemy;

	if (EnemyNameText)
	{
		EnemyNameText->SetText(EnemyName);
	}

	if (LevelText)
	{
		LevelText->SetText(FText::AsNumber(Level));
	}

	ShowHealthbar();
}

void UW_EnemyHealthbar::UpdateHealth(float CurrentHealth, float MaxHealth)
{
	float HealthPercent = MaxHealth > 0.0f ? CurrentHealth / MaxHealth : 0.0f;

	if (HealthBar)
	{
		HealthBar->SetPercent(HealthPercent);
	}
}

void UW_EnemyHealthbar::UpdateStance(float CurrentStance, float MaxStance)
{
	if (StanceBar)
	{
		float StancePercent = MaxStance > 0.0f ? CurrentStance / MaxStance : 1.0f;
		StanceBar->SetPercent(StancePercent);
	}
}

void UW_EnemyHealthbar::ShowHealthbar()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UW_EnemyHealthbar::HideHealthbar()
{
	SetVisibility(ESlateVisibility::Collapsed);
	TrackedEnemy = nullptr;
}
