// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlazingMoonGameInstance.h"
#include "GameFramework/SaveGame.h"
#include "BlazingMoonSave.generated.h"

class UGameProgression;
/**
 * 
 */
UCLASS()
class BLAZINGMOON_API UBlazingMoonSave : public USaveGame
{
	GENERATED_BODY()

	FBlazingMoonGameState GameState;
	FBlazingMoonPlayerState PlayerState;
	FName Level;

public:
	UFUNCTION(BlueprintCallable)
	void LoadGame();
	void SaveGame(FBlazingMoonGameState Game, FBlazingMoonPlayerState Player);
};
