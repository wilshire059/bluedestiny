#include "W_AbilityDisplay.h"

void UW_AbilityDisplay::SetupAbility(UTexture2D* Icon, FText AbilityName)
{
	if (AbilityIcon && Icon)
	{
		AbilityIcon->SetBrushFromTexture(Icon);
	}

	if (AbilityNameText)
	{
		AbilityNameText->SetText(AbilityName);
	}
}

void UW_AbilityDisplay::UpdateCooldown(float CurrentCooldown, float MaxCooldown)
{
	float Progress = MaxCooldown > 0.0f ? 1.0f - (CurrentCooldown / MaxCooldown) : 1.0f;

	if (CooldownBar)
	{
		CooldownBar->SetPercent(Progress);
	}

	if (CooldownText)
	{
		if (CurrentCooldown > 0.0f)
		{
			CooldownText->SetText(FText::AsNumber(FMath::CeilToInt(CurrentCooldown)));
			CooldownText->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			CooldownText->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void UW_AbilityDisplay::SetAbilityEnabled(bool bEnabled)
{
	if (AbilityIcon)
	{
		AbilityIcon->SetColorAndOpacity(bEnabled ? FLinearColor::White : FLinearColor(0.5f, 0.5f, 0.5f, 1.0f));
	}
}
