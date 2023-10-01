// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_RandomPatrol.generated.h"

/**
 * 
 */
UCLASS()
class BLAZINGMOON_API UBTService_RandomPatrol : public UBTService_BlackboardBase
{
	GENERATED_BODY()

	UBTService_RandomPatrol();

	UPROPERTY(EditAnywhere)
	float PatrolRadius;

	UPROPERTY(EditAnywhere)
	float MinimumRadius;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector HomeVector;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
