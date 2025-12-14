#include "W_Debug_ComponentSlot.h"

void UW_Debug_ComponentSlot::NativeConstruct()
{
	Super::NativeConstruct();

	if (SlotButton)
	{
		SlotButton->OnClicked.AddDynamic(this, &UW_Debug_ComponentSlot::HandleSlotClicked);
	}
}

void UW_Debug_ComponentSlot::SetupSlot(UActorComponent* Component)
{
	TrackedComponent = Component;

	if (ComponentNameText && Component)
	{
		ComponentNameText->SetText(FText::FromString(Component->GetName()));
	}
}

void UW_Debug_ComponentSlot::HandleSlotClicked()
{
	if (TrackedComponent.IsValid())
	{
		OnDebugComponentSelected.Broadcast(TrackedComponent.Get());
	}
}
