#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Internationalization/Text.h"
#include "W_ItemInfoEntry.generated.h"

UCLASS()
class SLF_5_7_API UW_ItemInfoEntry : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Content")
	FText EntryNameText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Content")
	int32 Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Content")
	double CurrentStatValue;

	// Components
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* EntryText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* ValueText;

protected:
	virtual void NativeConstruct() override;
};
