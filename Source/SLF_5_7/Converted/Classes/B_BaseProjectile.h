#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/BPI_Projectile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "B_BaseProjectile.generated.h"

UCLASS(Blueprintable, BlueprintType)
class SLF_5_7_API AB_BaseProjectile : public AActor, public IBPI_Projectile
{
	GENERATED_BODY()

public:
	AB_BaseProjectile();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USphereComponent> CollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> ProjectileMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float LifeSpan;

	// BPI_Projectile Interface
	virtual void InitializeProjectile_Implementation(AActor* TargetActor) override;

	// Custom projectile events
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Projectile")
	void OnProjectileLaunched(AActor* InstigatorActor, FVector Direction);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Projectile")
	void OnProjectileHit(AActor* HitActor, const FHitResult& HitResult);

protected:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
