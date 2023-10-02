// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BlazingMoonGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FBlazingMoonPlayerState
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Health=100;
	
	//Weapons
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool HasFlail=false;
	
};

USTRUCT(BlueprintType)
struct FBlazingMoonGameState
{
	GENERATED_BODY()
	FBlazingMoonGameState() = default;

	bool HasSunRock;
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	FString PreviousLevel;	
public:
	FORCEINLINE FBlazingMoonGameState* GetGameStatePtr() {return &GameState;}
	UFUNCTION(BlueprintCallable)
	FORCEINLINE FBlazingMoonGameState GetGameState() const {return GameState;}
	FORCEINLINE FBlazingMoonPlayerState* GetPlayerStatePtr() {return &PlayerState;}
	UFUNCTION(BlueprintCallable)
	FORCEINLINE FBlazingMoonPlayerState GetPlayerState() const {return PlayerState;}
	UFUNCTION(BlueprintCallable)
	FORCEINLINE FString GetPreviousLevel() const {return PreviousLevel;}

	FORCEINLINE void UpdateGameState(const FBlazingMoonGameState NewGameState) {GameState=NewGameState;}
	FORCEINLINE void UpdatePlayerState(const FBlazingMoonPlayerState NewPlayerState) {PlayerState = NewPlayerState;}
	FORCEINLINE void SetPreviousLevel(FString levelName) {PreviousLevel = levelName;}
};
