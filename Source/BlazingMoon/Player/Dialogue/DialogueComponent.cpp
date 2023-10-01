// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueComponent.h"

#include "DialogueData.h"
#include "BlazingMoon/BlazingMoon.h"
#include "BlazingMoon/Player/BlazingMoonCharacter.h"


// Sets default values for this component's properties
UDialogueComponent::UDialogueComponent(): Player(nullptr), DialogueData(nullptr)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDialogueComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


void UDialogueComponent::Interact(APlayerController* PlayerController)
{
	IInteractInterface::Interact(PlayerController);

	if (Initial)
	{
		Player = Cast<ABlazingMoonCharacter>(PlayerController->GetCharacter());
		Player->SetupDialogue();
		DialogueIndex=0;
		Initial = false;
	}
	FString st;
	if (DialogueData->GetParagraph(st, DialogueIndex))
	{
		if (Player) Player->FillDialogue(st);
		DialogueIndex++;
	}
	else
	{
		Player->DestroyDialogue();
		Initial = true;
	}
}

// Called every frame
void UDialogueComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}