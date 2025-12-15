#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "PC_Menu_SoulslikeFramework.generated.h"

class UUserWidget;
class UAC_SaveLoadManager;

UCLASS()
class SLF_5_7_API APC_Menu_SoulslikeFramework : public APlayerController
{
	GENERATED_BODY()

public:
	APC_Menu_SoulslikeFramework();

protected:
	virtual void BeginPlay() override;

	// Create and display the main menu widget
	UFUNCTION(BlueprintCallable, Category = "Menu")
	void CreateMainMenu();

	// Check if a saved game exists
	UFUNCTION(BlueprintCallable, Category = "Save")
	bool DoesSaveGameExist() const;

	// Main menu widget class to spawn
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> MainMenuWidgetClass;

	// Reference to the spawned main menu widget
	UPROPERTY(BlueprintReadOnly, Category = "UI")
	TObjectPtr<UUserWidget> MainMenuWidget;

	// Save/Load manager component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UAC_SaveLoadManager> SaveLoadManager;

	// Tag used for navigable widget focus
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	FGameplayTag NavigableWidgetTag;
};
