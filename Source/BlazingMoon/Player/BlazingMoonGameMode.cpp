// Copyright Epic Games, Inc. All Rights Reserved.

#include "BlazingMoonGameMode.h"
#include "BlazingMoonCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABlazingMoonGameMode::ABlazingMoonGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
