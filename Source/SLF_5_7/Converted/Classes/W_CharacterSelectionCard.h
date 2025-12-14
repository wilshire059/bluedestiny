#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "W_CharacterSelectionCard.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterCardSelected, int32, CardIndex);

UCLASS()
class SLF_5_7_API UW_CharacterSelectionCard : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> CardButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> CharacterImage;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> CharacterNameText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> ClassNameText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UVerticalBox> StatsContainer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	int32 CardIndex = 0;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnCharacterCardSelected OnCharacterCardSelected;

	UFUNCTION(BlueprintCallable, Category = "CharacterSelection")
	void SetSelected(bool bSelected);

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void HandleCardClicked();
};
