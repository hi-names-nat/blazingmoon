// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BlazingMoonGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FBlazingMoonPlayerState
{
	GENERATED_BODY()

	FBlazingMoonPlayerState() = default;
	bool HasSunRock =false;

	//Weapons
	UPROPERTY(EditDefaultsOnly)
	bool HasFlail=false;
	UPROPERTY(EditDefaultsOnly)
	bool HasBow=false;
	UPROPERTY(EditDefaultsOnly)
	uint32 Health=0;
};

USTRUCT(BlueprintType)
struct FBlazingMoonGameState
{
	GENERATED_BODY()
	FBlazingMoonGameState() = default;
};

/**
 * 
 */
UCLASS()
class BLAZINGMOON_API UBlazingMoonGameInstance : public UGameInstance
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	FBlazingMoonPlayerState PlayerState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	FBlazingMoonGameState GameState;

	
public:
	FORCEINLINE FBlazingMoonPlayerState* GetPlayerState() {return &PlayerState;}
	FORCEINLINE void UpdateGameState(FBlazingMoonGameState NewGameState) {GameState=NewGameState;}
	FORCEINLINE void UpdatePlayerState(FBlazingMoonPlayerState NewPlayerState) {PlayerState = NewPlayerState;}
};
