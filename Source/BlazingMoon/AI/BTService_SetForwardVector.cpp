// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SetForwardVector.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"


void UBTService_SetForwardVector::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
		OwnerComp.GetBlackboardComponent()->SetValueAsRotator(GetSelectedBlackboardKey(), OwnerComp.GetAIOwner()->GetPawn()->GetActorRotation());
}
