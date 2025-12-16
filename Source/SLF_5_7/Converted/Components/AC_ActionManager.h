#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "Enums/E_Direction.h"
#include "Enums/E_ValueType.h"
#include "Structs/FStatInfo.h"
#include "AC_ActionManager.generated.h"

class UB_Action;
class UPDA_Action;
class UDataTable;
class UAC_StatManager;
class UB_Stat;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDirectionChanged, E_Direction, NewDirection);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActionPerformed, FGameplayTag, ActionTag, bool, bSuccess);

UCLASS(ClassGroup=(Custom), Blueprintable, meta=(BlueprintSpawnableComponent))
class SLF_5_7_API UAC_ActionManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UAC_ActionManager();

	// ============================================================
	// PROPERTIES
	// ============================================================

	UPROPERTY(BlueprintAssignable, Category = "Action")
	FOnDirectionChanged OnDirectionChanged;

	UPROPERTY(BlueprintAssignable, Category = "Action")
	FOnActionPerformed OnActionPerformed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Action|Movement")
	E_Direction MovementDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Action|Movement")
	FVector2D MovementVector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Action|Movement")
	bool bIsOnLadder;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Action|Actions")
	TMap<FGameplayTag, TObjectPtr<UB_Action>> AvailableActions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action|Configuration")
	TMap<FGameplayTag, TSoftClassPtr<UB_Action>> Actions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action|Configuration")
	TObjectPtr<UDataTable> OverrideTable;

	// Caches for async loading
	UPROPERTY(Transient)
	TArray<FGameplayTag> ActionTagsCache;

	UPROPERTY(Transient)
	TArray<TObjectPtr<UPDA_Action>> ActionAssetsCache;

	// Timer for stamina management
	UPROPERTY()
	FTimerHandle StaminaLossTimer;

	// Stat tracking
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Action|Stats")
	TMap<FGameplayTag, FStatInfo> ActiveStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action|Stats")
	double MinValue;

	// ============================================================
	// MOVEMENT DIRECTION
	// ============================================================

	UFUNCTION(BlueprintCallable, Category = "Action|Movement")
	void SetMoveDir(FVector2D IAMove);

	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Action|Movement")
	void SRV_SetDirection(E_Direction Direction);

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category = "Action|Movement")
	void MC_SetDirection(E_Direction Direction);

	UFUNCTION(BlueprintPure, Category = "Action|Movement")
	bool GetIsMoving2D() const;

	// ============================================================
	// ACTION SYSTEM
	// ============================================================

	UFUNCTION(BlueprintCallable, Category = "Action")
	void PerformAction(FGameplayTag ActionTag);

	UFUNCTION(BlueprintCallable, Category = "Action")
	void RecursiveLoadActions();

	// ============================================================
	// STAT HELPERS
	// ============================================================

	UFUNCTION(BlueprintPure, Category = "Action|Stats")
	UAC_StatManager* GetStatManager() const;

	UFUNCTION(BlueprintPure, Category = "Action|Stats")
	double GetStat(FGameplayTag StatTag) const;

	UFUNCTION(BlueprintCallable, Category = "Action|Stats")
	void AdjustStat(FGameplayTag StatTag, double Change, E_ValueType ValueType);

	UFUNCTION(BlueprintCallable, Category = "Action|Stats")
	void AdjustValue(FGameplayTag StatTag, double Change, E_ValueType ValueType);

	UFUNCTION(BlueprintPure, Category = "Action|Stats")
	bool IsStatMoreThan(FGameplayTag StatTag, double CompareValue) const;

	// ============================================================
	// SPRINTING / STAMINA
	// ============================================================

	UFUNCTION(BlueprintCallable, Category = "Action|Stamina")
	void StartStaminaLoss();

	UFUNCTION(BlueprintCallable, Category = "Action|Stamina")
	void ReduceStamina();

	UFUNCTION(BlueprintCallable, Category = "Action|Stamina")
	void StopStaminaLoss();

	UFUNCTION(BlueprintCallable, Category = "Action|Stamina")
	void StartStaminaRegen();

	// ============================================================
	// UTILITY
	// ============================================================

	UFUNCTION(BlueprintPure, Category = "Action|Utility")
	FString ParseOutTagName(FGameplayTag Tag) const;

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	E_Direction CalculateDirectionFromAngle(double Degrees) const;
};
