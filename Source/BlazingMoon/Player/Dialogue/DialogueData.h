// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlazingMoon/Player/InteractInterface.h"
#include "Engine/DataAsset.h"
#include "DialogueData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class BLAZINGMOON_API UDialogueData : public UDataAsset
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	TArray<FString> DialogueEntry;
	
public:

	UFUNCTION()
	bool GetParagraph(FString& Chunk, int32 Index);
};
