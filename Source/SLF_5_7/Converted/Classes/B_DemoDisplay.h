#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "B_DemoDisplay.generated.h"

UCLASS(Blueprintable, BlueprintType)
class SLF_5_7_API AB_DemoDisplay : public AActor
{
	GENERATED_BODY()

public:
	AB_DemoDisplay();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UTextRenderComponent> TextDisplay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display")
	FText DisplayText;
};
