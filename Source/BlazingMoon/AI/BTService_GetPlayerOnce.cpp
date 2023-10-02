// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_GetPlayerOnce.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void UBTService_GetPlayerOnce::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (!hasTriggered)
	{
		APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Player->GetActorLocation());
	}
}
