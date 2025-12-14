#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "W_Radar_TrackedElement.generated.h"

UCLASS()
class SLF_5_7_API UW_Radar_TrackedElement : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> ElementIcon;

	UPROPERTY(BlueprintReadWrite, Category = "State")
	TWeakObjectPtr<AActor> TrackedActor;

	UFUNCTION(BlueprintCallable, Category = "Radar")
	void SetTrackedActor(AActor* Actor, UTexture2D* Icon);

	UFUNCTION(BlueprintCallable, Category = "Radar")
	void UpdatePosition(FVector2D RadarPosition);

	UFUNCTION(BlueprintCallable, Category = "Radar")
	bool IsActorValid() const;
};
