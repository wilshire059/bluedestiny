#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "B_DemoRoom.generated.h"

UCLASS(Blueprintable, BlueprintType)
class SLF_5_7_API AB_DemoRoom : public AActor
{
	GENERATED_BODY()

public:
	AB_DemoRoom();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Demo")
	FName RoomName;
};
