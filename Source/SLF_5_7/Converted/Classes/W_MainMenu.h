#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "W_MainMenu.generated.h"

class UW_MainMenu_Button;

UCLASS()
class SLF_5_7_API UW_MainMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UVerticalBox> ButtonContainer;

	UPROPERTY(BlueprintReadWrite, Category = "Menu")
	TArray<UW_MainMenu_Button*> MenuButtons;

	UFUNCTION(BlueprintCallable, Category = "Menu")
	void OnMenuOpened();

	UFUNCTION(BlueprintCallable, Category = "Menu")
	void OnMenuClosed();

	UFUNCTION(BlueprintCallable, Category = "Menu")
	void OnMenuButtonClicked(int32 ButtonIndex);

	UFUNCTION(BlueprintCallable, Category = "Menu")
	void NewGame();

	UFUNCTION(BlueprintCallable, Category = "Menu")
	void ContinueGame();

	UFUNCTION(BlueprintCallable, Category = "Menu")
	void LoadGame();

	UFUNCTION(BlueprintCallable, Category = "Menu")
	void Settings();

	UFUNCTION(BlueprintCallable, Category = "Menu")
	void QuitGame();

protected:
	virtual void NativeConstruct() override;
};
