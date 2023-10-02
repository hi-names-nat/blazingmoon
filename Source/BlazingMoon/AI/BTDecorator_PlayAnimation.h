// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BehaviorTree/BTService.h"
#include "BTDecorator_PlayAnimation.generated.h"

/**
 * 
 */
UCLASS()
class BLAZINGMOON_API UBTDecorator_PlayAnimation : public UBTDecorator
{
	GENERATED_BODY()

	bool hasTriggered = false;

	UPROPERTY(EditAnywhere)
	UAnimationAsset* AnimationAsset;

	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
