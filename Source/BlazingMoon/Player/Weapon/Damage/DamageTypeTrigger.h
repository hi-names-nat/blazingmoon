// (c) Dark Frog SGS 2023.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "DamageInterface.h"
#include "DamageTypeTrigger.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCorrectDamageType);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BLAZINGMOON_API UDamageTypeTrigger : public UBoxComponent, public IDamageInterface
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, Category = Callbacks)
	FOnCorrectDamageType OnCorrectDamage;

	//Damage is agnostic on this. Change for extraneous behavior later if possible.
	virtual void DamageObject(float amount, UDamageType* DamageType) override;
	
protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageType> ExpectedDamageType;

public:
};

