#pragma once

#include "CoreMinimal.h"
#include "W_UserWidget_Base.h"
#include "Components/CanvasPanel.h"
#include "W_Radar.generated.h"

UCLASS()
class SLF_5_7_API UW_Radar : public UW_UserWidget_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UCanvasPanel> RadarCanvas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Radar")
	float RadarRange = 5000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Radar")
	float RadarSize = 200.0f;

	UFUNCTION(BlueprintCallable, Category = "Radar")
	void UpdateRadar();

	UFUNCTION(BlueprintCallable, Category = "Radar")
	FVector2D WorldToRadarPosition(FVector WorldLocation) const;

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Radar")
	void OnUpdateRadar();
};
