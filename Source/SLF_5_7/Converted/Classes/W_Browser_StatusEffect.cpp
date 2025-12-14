#include "W_Browser_StatusEffect.h"

void UW_Browser_StatusEffect::NativeConstruct()
{
	Super::NativeConstruct();
	if (EffectButton)
	{
		EffectButton->OnClicked.AddDynamic(this, &UW_Browser_StatusEffect::HandleEffectClicked);
	}
}

void UW_Browser_StatusEffect::SetupEffect(int32 InIndex, FText EffectName, UTexture2D* Icon)
{
	EffectIndex = InIndex;
	if (EffectNameText) EffectNameText->SetText(EffectName);
	if (EffectIcon && Icon) EffectIcon->SetBrushFromTexture(Icon);
}

void UW_Browser_StatusEffect::HandleEffectClicked()
{
	OnBrowserStatusEffectSelected.Broadcast(EffectIndex);
}
