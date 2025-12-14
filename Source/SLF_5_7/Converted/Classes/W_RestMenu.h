#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "Components/VerticalBox.h"
#include "W_RestMenu.generated.h"

class UW_RestMenu_Button;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRestMenuAction, int32, ActionIndex);

UCLASS()
class SLF_5_7_API UW_RestMenu : public UW_UserWidget_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UVerticalBox> ButtonContainer;

	UPROPERTY(BlueprintReadWrite, Category = "Menu")
	TArray<UW_RestMenu_Button*> MenuButtons;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnRestMenuAction OnRestMenuAction;

	UFUNCTION(BlueprintCallable, Category = "RestMenu")
	void OnButtonClicked(int32 ButtonIndex);

	UFUNCTION(BlueprintCallable, Category = "RestMenu")
	void LevelUp();

	UFUNCTION(BlueprintCallable, Category = "RestMenu")
	void PassTime();

	UFUNCTION(BlueprintCallable, Category = "RestMenu")
	void SortChest();

	UFUNCTION(BlueprintCallable, Category = "RestMenu")
	void LeaveRestPoint();
};
