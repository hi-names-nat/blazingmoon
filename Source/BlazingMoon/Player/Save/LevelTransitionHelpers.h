// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LevelTransitionHelpers.generated.h"

USTRUCT(BlueprintType)
struct FSearchState
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool FoundValue = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Location;

	FSearchState() {Location = FVector::Zero();}
	
	FSearchState(bool bFoundValue, FVector vector)
	{
		Location = vector;
		FoundValue = bFoundValue;
	}
};

/**
 * 
 */
UCLASS()
class BLAZINGMOON_API ULevelTransitionHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	static FSearchState FindMatchingEntryLocation(TArray<AActor*> Actors, FString SearchTerm);  
};
