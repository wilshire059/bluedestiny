#include "W_Utility_Component.h"

void UW_Utility_Component::NativeConstruct()
{
	Super::NativeConstruct();

	if (ComponentButton)
	{
		ComponentButton->OnClicked.AddDynamic(this, &UW_Utility_Component::HandleComponentClicked);
	}
}

void UW_Utility_Component::SetupComponent(UActorComponent* Component)
{
	TrackedComponent = Component;

	if (Component)
	{
		if (ComponentNameText)
		{
			ComponentNameText->SetText(FText::FromString(Component->GetName()));
		}

		if (ComponentTypeText)
		{
			ComponentTypeText->SetText(FText::FromString(Component->GetClass()->GetName()));
		}
	}
}

void UW_Utility_Component::HandleComponentClicked()
{
	if (TrackedComponent.IsValid())
	{
		OnUtilityComponentSelected.Broadcast(TrackedComponent.Get());
	}
}
