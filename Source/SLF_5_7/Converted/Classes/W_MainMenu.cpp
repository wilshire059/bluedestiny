#include "W_MainMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UW_MainMenu::NativeConstruct()
{
	Super::NativeConstruct();
}

void UW_MainMenu::OnMenuOpened()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UW_MainMenu::OnMenuClosed()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UW_MainMenu::OnMenuButtonClicked(int32 ButtonIndex)
{
	switch (ButtonIndex)
	{
	case 0:
		NewGame();
		break;
	case 1:
		ContinueGame();
		break;
	case 2:
		LoadGame();
		break;
	case 3:
		Settings();
		break;
	case 4:
		QuitGame();
		break;
	default:
		break;
	}
}

void UW_MainMenu::NewGame()
{
	// Implemented in Blueprint
}

void UW_MainMenu::ContinueGame()
{
	// Implemented in Blueprint
}

void UW_MainMenu::LoadGame()
{
	// Implemented in Blueprint
}

void UW_MainMenu::Settings()
{
	// Implemented in Blueprint
}

void UW_MainMenu::QuitGame()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}
