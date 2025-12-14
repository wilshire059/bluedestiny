#include "W_NPC_Window.h"

void UW_NPC_Window::SetupNPCWindow(FText NPCName, const TArray<FText>& Options)
{
	if (NPCNameText)
	{
		NPCNameText->SetText(NPCName);
	}

	OnSetupOptions(Options);
}

void UW_NPC_Window::SelectOption(int32 OptionIndex)
{
	OnNPCOptionSelected.Broadcast(OptionIndex);
}

void UW_NPC_Window::CloseWindow()
{
	RemoveFromParent();
}
