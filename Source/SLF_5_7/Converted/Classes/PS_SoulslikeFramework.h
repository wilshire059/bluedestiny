#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PS_SoulslikeFramework.generated.h"

UCLASS()
class SLF_5_7_API APS_SoulslikeFramework : public APlayerState
{
	GENERATED_BODY()

public:
	APS_SoulslikeFramework();

protected:
	// Override to handle player state copying when seamless travel occurs
	virtual void CopyProperties(APlayerState* PlayerState) override;

	// Override to handle receiving properties from old player state
	virtual void OverrideWith(APlayerState* PlayerState) override;
};
