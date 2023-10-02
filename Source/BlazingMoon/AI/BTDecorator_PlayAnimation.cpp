// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_PlayAnimation.h"

#include "AIController.h"
#include "GameFramework/Character.h"

void UBTDecorator_PlayAnimation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (!hasTriggered)
	{
		ACharacter* Character = OwnerComp.GetAIOwner()->GetCharacter();
		Character->GetMesh()->SetAnimation(AnimationAsset);
	}
}
