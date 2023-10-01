// (c) Dark Frog SGS 2023.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Damage/DamageInterface.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnKilled);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHurt);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BLAZINGMOON_API UHealthComponent : public UBoxComponent, public IDamageInterface
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, Category = Callbacks)
	FOnKilled OnKilled;

	UPROPERTY(BlueprintAssignable, Category = Callbacks)
	FOnKilled OnHurt;
	
	UPROPERTY(EditDefaultsOnly, Category=Health)
	float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere, Category=Health, BlueprintReadOnly)
	float CurrentHealth;
	
	UFUNCTION(BlueprintCallable)
	void TakeDamage(float Amount);

	//Damage is agnostic on this. Change for extraneous behavior later if possible.
	virtual void DamageObject(float amount, UDamageType* DamageType) override {TakeDamage(amount);};

	UFUNCTION(BlueprintCallable)
	void HealDamage(const float Amount) {CurrentHealth += Amount; if (CurrentHealth > MaxHealth) CurrentHealth = MaxHealth;}

	void SetHealth(const float Amount) {CurrentHealth = Amount;}
	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
};
