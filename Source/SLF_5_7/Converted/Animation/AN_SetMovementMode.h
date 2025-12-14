#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AN_SetMovementMode.generated.h"

UCLASS()
class SLF_5_7_API UAN_SetMovementMode : public UAnimNotify
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	TEnumAsByte<EMovementMode> MovementMode = MOVE_Walking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	uint8 CustomMode = 0;

	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
