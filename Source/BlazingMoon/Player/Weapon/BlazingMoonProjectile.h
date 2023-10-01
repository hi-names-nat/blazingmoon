// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlazingMoonProjectile.generated.h"

class UProjectileMovementComponent;

UCLASS()
class BLAZINGMOON_API ABlazingMoonProjectile : public AActor
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	// Sets default values for this actor's properties
	ABlazingMoonProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditDefaultsOnly)
	class USphereComponent* ColliderComponent;

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess="true"))
	int Damage;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
