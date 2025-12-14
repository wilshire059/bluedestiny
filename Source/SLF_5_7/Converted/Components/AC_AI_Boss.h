#include "Components/AC_StatManager.h"
#include "Structs/FAiBossPhase.h"
#include "AC_AI_Boss.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBossPhaseChanged, int32, NewPhaseIndex);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SLF_5_7_API UAC_AI_Boss : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAC_AI_Boss();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Boss")
    FText BossName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Boss")
    TArray<FAiBossPhase> Phases;

    UPROPERTY(BlueprintAssignable, Category = "AI Boss")
    FOnBossPhaseChanged OnBossPhaseChanged;

    UFUNCTION(BlueprintCallable, Category = "AI Boss")
	void InitializeBoss(FText Name, float MaxHealth);

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnStatUpdated(UB_Stat* Stat, double Amount, double Percent);

    void HandlePhaseChange(const FAiBossPhase& NewPhase, int32 PhaseIndex);
};
