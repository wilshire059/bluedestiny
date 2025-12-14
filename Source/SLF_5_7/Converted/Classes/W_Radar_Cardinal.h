#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Structs/FCardinalData.h"
#include "W_Radar_Cardinal.generated.h"

UCLASS()
class SLF_5_7_API UW_Radar_Cardinal : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> CardinalText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cardinal")
	FCardinalData CardinalData;

	UFUNCTION(BlueprintCallable, Category = "Cardinal")
	void SetupCardinal(const FCardinalData& Data);

protected:
	virtual void NativePreConstruct() override;
};
