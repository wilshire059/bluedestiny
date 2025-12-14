#include "B_BaseProjectile.h"

AB_BaseProjectile::AB_BaseProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetSphereRadius(15.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	CollisionComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	CollisionComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RootComponent = CollisionComponent;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 3000.0f;
	ProjectileMovement->MaxSpeed = 3000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.0f;

	Damage = 50.0f;
	Speed = 3000.0f;
	LifeSpan = 5.0f;
}

void AB_BaseProjectile::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(LifeSpan);

	if (CollisionComponent)
	{
		CollisionComponent->OnComponentHit.AddDynamic(this, &AB_BaseProjectile::OnHit);
		CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AB_BaseProjectile::OnOverlap);
	}
}

void AB_BaseProjectile::InitializeProjectile_Implementation(AActor* TargetActor)
{
	if (TargetActor && ProjectileMovement)
	{
		FVector Direction = (TargetActor->GetActorLocation() - GetActorLocation()).GetSafeNormal();
		ProjectileMovement->Velocity = Direction * Speed;
	}
}

void AB_BaseProjectile::OnProjectileLaunched_Implementation(AActor* InstigatorActor, FVector Direction)
{
	if (ProjectileMovement)
	{
		ProjectileMovement->Velocity = Direction * Speed;
	}
}

void AB_BaseProjectile::OnProjectileHit_Implementation(AActor* HitActor, const FHitResult& HitResult)
{
	// Apply damage and destroy - implement in Blueprint
}

void AB_BaseProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	OnProjectileHit(OtherActor, Hit);
	Destroy();
}

void AB_BaseProjectile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetOwner())
	{
		OnProjectileHit(OtherActor, SweepResult);
		Destroy();
	}
}
