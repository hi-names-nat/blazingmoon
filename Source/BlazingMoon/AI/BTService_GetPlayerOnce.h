// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_GetPlayerOnce.generated.h"

/**
 * 
 */
UCLASS()
class BLAZINGMOON_API UBTService_GetPlayerOnce : public UBTService_BlackboardBase
{
	GENERATED_BODY()

	bool hasTriggered = false;


	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
