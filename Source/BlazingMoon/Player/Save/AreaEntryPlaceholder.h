// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AreaEntryPlaceholder.generated.h"

UCLASS()
class BLAZINGMOON_API AAreaEntryPlaceholder : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAreaEntryPlaceholder();

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UWorld> TriggerLevel;

	UFUNCTION(BlueprintCallable)
	FORCEINLINE FString TriggerLevelName() const {return TriggerLevel->GetName();}
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};