#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AC_RadarElement.generated.h"

UENUM(BlueprintType)
enum class E_RadarElementType : uint8
{
	Enemy UMETA(DisplayName = "Enemy"),
	Friendly UMETA(DisplayName = "Friendly"),
	Neutral UMETA(DisplayName = "Neutral"),
	Objective UMETA(DisplayName = "Objective"),
	Item UMETA(DisplayName = "Item")
};

UCLASS(ClassGroup=(Custom), Blueprintable, meta=(BlueprintSpawnableComponent))
class SLF_5_7_API UAC_RadarElement : public UActorComponent
{
	GENERATED_BODY()

public:
	UAC_RadarElement();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Radar")
	E_RadarElementType ElementType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Radar")
	TSoftObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Radar")
	FLinearColor Color;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Radar")
	bool bShowOnRadar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Radar")
	float IconScale;

	UFUNCTION(BlueprintCallable, Category = "Radar")
	void SetVisible(bool bVisible);

	UFUNCTION(BlueprintPure, Category = "Radar")
	bool IsVisible() const;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
