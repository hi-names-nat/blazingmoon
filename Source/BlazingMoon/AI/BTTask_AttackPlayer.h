// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_AttackPlayer.generated.h"

/**
 * 
 */
UCLASS()
class BLAZINGMOON_API UBTTask_AttackPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float AttackDistance;

	UPROPERTY(EditAnywhere)
	float Damage;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
