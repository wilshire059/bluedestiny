#include "W_Browser_WeaponAbility.h"

void UW_Browser_WeaponAbility::NativeConstruct()
{
	Super::NativeConstruct();
	if (AbilityButton)
	{
		AbilityButton->OnClicked.AddDynamic(this, &UW_Browser_WeaponAbility::HandleAbilityClicked);
	}
}

void UW_Browser_WeaponAbility::SetupAbility(int32 InIndex, FText AbilityName, UTexture2D* Icon)
{
	AbilityIndex = InIndex;
	if (AbilityNameText) AbilityNameText->SetText(AbilityName);
	if (AbilityIcon && Icon) AbilityIcon->SetBrushFromTexture(Icon);
}

void UW_Browser_WeaponAbility::HandleAbilityClicked()
{
	OnBrowserWeaponAbilitySelected.Broadcast(AbilityIndex);
}
