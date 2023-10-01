// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlazingMoon/Player/InteractInterface.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "DialogueComponent.generated.h"


class UDialogueData;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BLAZINGMOON_API UDialogueComponent : public USphereComponent, public IInteractInterface
{
	GENERATED_BODY()

	class ABlazingMoonCharacter* Player;

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess="true"))
	UDialogueData* DialogueData;

	int32 DialogueIndex = 0;
	bool Initial = true;

public:
	// Sets default values for this component's properties
	UDialogueComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	virtual void Interact(APlayerController* PlayerController) override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

};
