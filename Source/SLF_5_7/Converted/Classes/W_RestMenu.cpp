#include "W_RestMenu.h"

void UW_RestMenu::OnButtonClicked(int32 ButtonIndex)
{
	OnRestMenuAction.Broadcast(ButtonIndex);

	switch (ButtonIndex)
	{
	case 0:
		LevelUp();
		break;
	case 1:
		PassTime();
		break;
	case 2:
		SortChest();
		break;
	case 3:
		LeaveRestPoint();
		break;
	default:
		break;
	}
}

void UW_RestMenu::LevelUp()
{
	// Implemented in Blueprint
}

void UW_RestMenu::PassTime()
{
	// Implemented in Blueprint
}

void UW_RestMenu::SortChest()
{
	// Implemented in Blueprint
}

void UW_RestMenu::LeaveRestPoint()
{
	// Implemented in Blueprint
	RemoveFromParent();
}
