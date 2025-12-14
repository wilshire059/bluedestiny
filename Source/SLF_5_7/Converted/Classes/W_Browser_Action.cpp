#include "W_Browser_Action.h"

void UW_Browser_Action::NativeConstruct()
{
	Super::NativeConstruct();

	if (ActionButton)
	{
		ActionButton->OnClicked.AddDynamic(this, &UW_Browser_Action::HandleActionClicked);
	}
}

void UW_Browser_Action::SetupAction(int32 InActionIndex, FText ActionName, UTexture2D* Icon)
{
	ActionIndex = InActionIndex;

	if (ActionNameText)
	{
		ActionNameText->SetText(ActionName);
	}

	if (ActionIcon && Icon)
	{
		ActionIcon->SetBrushFromTexture(Icon);
	}
}

void UW_Browser_Action::HandleActionClicked()
{
	OnBrowserActionSelected.Broadcast(ActionIndex);
}
