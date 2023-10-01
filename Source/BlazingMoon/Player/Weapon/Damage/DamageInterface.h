// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Elements/Actor/ActorElementAssetDataInterface.h"
#include "DamageInterface.generated.h"

/**
 * 
 */
UINTERFACE()
class BLAZINGMOON_API UDamageInterface : public UInterface
{
	GENERATED_BODY()
};

class BLAZINGMOON_API IDamageInterface
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void DamageObject(float amount, UDamageType* DamageType) = 0;
	
};