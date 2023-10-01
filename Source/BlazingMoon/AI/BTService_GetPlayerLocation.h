// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_GetPlayerLocation.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class BLAZINGMOON_API UBTService_GetPlayerLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()

	UBTService_GetPlayerLocation();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
