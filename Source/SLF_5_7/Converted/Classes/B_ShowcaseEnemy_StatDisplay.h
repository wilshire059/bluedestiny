#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "B_ShowcaseEnemy_StatDisplay.generated.h"

UCLASS(Blueprintable, BlueprintType)
class SLF_5_7_API AB_ShowcaseEnemy_StatDisplay : public AActor
{
	GENERATED_BODY()

public:
	AB_ShowcaseEnemy_StatDisplay();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UWidgetComponent> StatWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display")
	AActor* LinkedEnemy;
};
