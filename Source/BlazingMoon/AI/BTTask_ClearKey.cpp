// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ClearKey.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ClearKey::UBTTask_ClearKey()
{
	NodeName = TEXT("Clear Blackboard Key");
}

EBTNodeResult::Type UBTTask_ClearKey::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	return EBTNodeResult::Succeeded;
	
}
