// Fill out your copyright notice in the Description page of Project Settings.


#include "BlazingMoonSave.h"

#include "Kismet/GameplayStatics.h"

void UBlazingMoonSave::LoadGame(UBlazingMoonGameInstance* GameInstance)
{
	UGameplayStatics::OpenLevel(GetWorld(), Level);
	GameInstance->UpdateGameState(GameState);
	GameInstance->UpdatePlayerState(PlayerState);
}

void UBlazingMoonSave::SaveGame(FBlazingMoonGameState Game, FBlazingMoonPlayerState Player)
{
	GameState = Game;
	PlayerState = Player;
}