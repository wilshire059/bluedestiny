#include "W_Browser_Animset.h"

void UW_Browser_Animset::NativeConstruct()
{
	Super::NativeConstruct();
	if (AnimsetButton)
	{
		AnimsetButton->OnClicked.AddDynamic(this, &UW_Browser_Animset::HandleAnimsetClicked);
	}
}

void UW_Browser_Animset::SetupAnimset(int32 InIndex, FText AnimsetName)
{
	AnimsetIndex = InIndex;
	if (AnimsetNameText)
	{
		AnimsetNameText->SetText(AnimsetName);
	}
}

void UW_Browser_Animset::HandleAnimsetClicked()
{
	OnBrowserAnimsetSelected.Broadcast(AnimsetIndex);
}
