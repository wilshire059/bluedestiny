#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DirectionalLight.h"
#include "Engine/SkyLight.h"
#include "B_SkyManager.generated.h"

UCLASS(Blueprintable, BlueprintType)
class SLF_5_7_API AB_SkyManager : public AActor
{
	GENERATED_BODY()

public:
	AB_SkyManager();

	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sky")
	AActor* SunLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sky")
	AActor* SkyLightActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sky")
	float TimeOfDay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sky")
	float TimeSpeed;

	UFUNCTION(BlueprintCallable, Category = "Sky")
	void SetTimeOfDay(float NewTime);

	UFUNCTION(BlueprintCallable, Category = "Sky")
	void UpdateSkyState();

protected:
	virtual void BeginPlay() override;
};
