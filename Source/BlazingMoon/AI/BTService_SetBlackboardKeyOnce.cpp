// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SetBlackboardKeyOnce.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"


void UBTService_SetBlackboardKeyOnce::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	if (!hasSet)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation());
	}
}
