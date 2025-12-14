#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "W_CharacterSelection.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterSelected, int32, CharacterIndex);

UCLASS()
class SLF_5_7_API UW_CharacterSelection : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UScrollBox> CharacterCardsContainer;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnCharacterSelected OnCharacterSelected;

	UFUNCTION(BlueprintCallable, Category = "CharacterSelection")
	void SelectCharacter(int32 CharacterIndex);

	UFUNCTION(BlueprintCallable, Category = "CharacterSelection")
	void ConfirmSelection();

protected:
	UPROPERTY(BlueprintReadWrite, Category = "State")
	int32 SelectedCharacterIndex = 0;

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "CharacterSelection")
	void OnSetupCharacters();
};
