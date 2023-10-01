// Fill out your copyright notice in the Description page of Project Settings.


#include "BlazingMoonProjectile.h"

#include "HealthComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


void ABlazingMoonProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (const auto HpC = Cast<UHealthComponent>(OtherComp))
	{
		HpC->TakeDamage(Damage);
	}
	Destroy();
}

// Sets default values
ABlazingMoonProjectile::ABlazingMoonProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Component"));
	ColliderComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	
	RootComponent = ColliderComponent;
	ColliderComponent->OnComponentHit.AddDynamic(this, &ABlazingMoonProjectile::OnHit);
}

// Called when the game starts or when spawned
void ABlazingMoonProjectile::BeginPlay()
{
	Super::BeginPlay();
	ColliderComponent->IgnoreActorWhenMoving(GetInstigator(), true);
	
}

// Called every frame
void ABlazingMoonProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

