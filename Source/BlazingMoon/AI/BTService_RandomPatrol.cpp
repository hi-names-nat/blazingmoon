// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_RandomPatrol.h"

#include <complex>

#include "BehaviorTree/BlackboardComponent.h"

UBTService_RandomPatrol::UBTService_RandomPatrol()
{
	NodeName = "Get Random Point within Radius from Home";

	
}

void UBTService_RandomPatrol::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	auto realRadius = FMath::RandRange(MinimumRadius, PatrolRadius);
	auto a = FMath::RandRange(0, 1);

	FVector PatrolGoal = FVector(realRadius * a, (1-a) * realRadius, 0);
	auto Home = OwnerComp.GetBlackboardComponent()->GetValueAsVector(HomeVector.SelectedKeyName);
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PatrolGoal + Home);
}
