#include "PC_Menu_SoulslikeFramework.h"
#include "AC_SaveLoadManager.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

APC_Menu_SoulslikeFramework::APC_Menu_SoulslikeFramework()
{
	// Create save/load manager component
	SaveLoadManager = CreateDefaultSubobject<UAC_SaveLoadManager>(TEXT("SaveLoadManager"));
}

void APC_Menu_SoulslikeFramework::BeginPlay()
{
	Super::BeginPlay();

	// Show mouse cursor for menu navigation
	SetShowMouseCursor(true);
	SetInputMode(FInputModeUIOnly());

	// Create the main menu
	CreateMainMenu();
}

void APC_Menu_SoulslikeFramework::CreateMainMenu()
{
	if (MainMenuWidgetClass)
	{
		MainMenuWidget = CreateWidget<UUserWidget>(this, MainMenuWidgetClass);
		if (MainMenuWidget)
		{
			MainMenuWidget->AddToViewport();
		}
	}
}

bool APC_Menu_SoulslikeFramework::DoesSaveGameExist() const
{
	// Check if a save game exists at slot 0
	return UGameplayStatics::DoesSaveGameExist(TEXT("SaveSlot"), 0);
}
