#include "W_Debug_ComponentTooltip.h"

void UW_Debug_ComponentTooltip::SetupTooltip(UActorComponent* Component)
{
	if (!Component)
	{
		return;
	}

	if (ComponentNameText)
	{
		ComponentNameText->SetText(FText::FromString(Component->GetName()));
	}

	if (ComponentClassText)
	{
		ComponentClassText->SetText(FText::FromString(Component->GetClass()->GetName()));
	}

	OnSetupProperties(Component);
}
