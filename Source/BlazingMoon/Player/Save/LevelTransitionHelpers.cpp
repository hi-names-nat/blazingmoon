// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelTransitionHelpers.h"

#include "AreaEntryPlaceholder.h"
#include "BlazingMoon/BlazingMoon.h"

FSearchState ULevelTransitionHelpers::FindMatchingEntryLocation(TArray<AActor*> Actors, FString SearchTerm)
{
	for(auto actor : Actors)
	{
		if (auto t = Cast<AAreaEntryPlaceholder>(actor))
		{
			UE_LOG(LogBlazingMoon, Log, TEXT("Searchterm: %s, Name: %s"), * SearchTerm, *t->TriggerLevel.GetAssetName());
			if (t->TriggerLevel.GetAssetName() == SearchTerm) return FSearchState(true, t->GetActorLocation());
		} 
	}
	return FSearchState(false, FVector::Zero());
}
