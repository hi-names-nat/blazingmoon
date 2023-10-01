// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_SetBlackboardKeyOnce.generated.h"

/**
 * 
 */
UCLASS()
class BLAZINGMOON_API UBTService_SetBlackboardKeyOnce : public UBTService_BlackboardBase
{
	GENERATED_BODY()

	bool hasSet = false;

	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
