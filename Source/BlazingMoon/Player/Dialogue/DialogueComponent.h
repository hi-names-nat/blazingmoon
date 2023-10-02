// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlazingMoon/Player/InteractInterface.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "DialogueComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDialogueBegin);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDialogueEnd);


class UDialogueData;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BLAZINGMOON_API UDialogueComponent : public USphereComponent, public IInteractInterface
{
	GENERATED_BODY()

	class ABlazingMoonCharacter* Player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	UDialogueData* DialogueData;

	int32 DialogueIndex = 0;
	bool Initial = true;

public:
	// Sets default values for this component's properties
	UDialogueComponent();

	UPROPERTY(BlueprintAssignable)
	FOnDialogueBegin OnDialogueBegin;
	
	UPROPERTY(BlueprintAssignable)
	FOnDialogueEnd OnDialogueEnd;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	virtual void Interact(APlayerController* PlayerController) override;
	

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

};
