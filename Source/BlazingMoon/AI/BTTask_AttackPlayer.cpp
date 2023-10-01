// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_AttackPlayer.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BlazingMoon/BlazingMoon.h"
#include "BlazingMoon/Player/Weapon/HealthComponent.h"

EBTNodeResult::Type UBTTask_AttackPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FHitResult OUT_Hit;
	FCollisionQueryParams Params;
	auto AIActor = OwnerComp.GetAIOwner()->GetPawn();
	auto Player = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());
	auto aim = (Player - AIActor->GetActorLocation()).GetSafeNormal() * AttackDistance;
	Params.AddIgnoredActor(AIActor);
	GetWorld()->LineTraceSingleByChannel(OUT_Hit, AIActor->GetActorLocation(), 
	AIActor->GetActorLocation() + aim,
	ECC_GameTraceChannel1
	);
	DrawDebugLine(GetWorld(), AIActor->GetActorLocation(), AIActor->GetActorLocation() + aim, FColor::Red, true);
	if (auto HpC = Cast<UHealthComponent>(OUT_Hit.GetComponent()))
	{
		HpC->TakeDamage(Damage);
		UE_LOG(LogBlazingMoon, Log, TEXT("Hit it"));
	}
	return EBTNodeResult::Succeeded;
}

