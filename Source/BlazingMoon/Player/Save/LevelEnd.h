// (c) Dark Frog SGS 2023.

#pragma once

#include "CoreMinimal.h"
#include "BlazingMoon/Player/InteractInterface.h"
#include "LevelEnd.generated.h"

UCLASS()
class BLAZINGMOON_API ALevelEnd : public AActor, public IInteractInterface
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	class UBoxComponent* CollisionMesh;
public:
	// Sets default values for this actor's properties
	ALevelEnd();
	
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UWorld> LevelToLoad;

	UPROPERTY(VisibleAnywhere)
	FString LevelName;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(APlayerController* PlayerController) override;
};