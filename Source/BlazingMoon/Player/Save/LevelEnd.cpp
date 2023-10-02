// (c) Dark Frog SGS 2023.


#include "LevelEnd.h"

#include "BlazingMoonSave.h"
#include "BlazingMoon/BlazingMoon.h"
#include "BlazingMoon/Player/BlazingMoonCharacter.h"
#include "GameFramework/SaveGame.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ALevelEnd::ALevelEnd()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	SetRootComponent(CollisionMesh);
}

// Called when the game starts or when spawned
void ALevelEnd::BeginPlay()
{
	Super::BeginPlay();

	
	LevelName = LevelToLoad->GetPathName();
}

// Called every frame
void ALevelEnd::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALevelEnd::Interact(APlayerController* PlayerController)
{
	if (const auto PlayerChar= Cast<ABlazingMoonCharacter>(PlayerController->GetPawn()))
	{
		const auto Instance = Cast<UBlazingMoonGameInstance>(GetGameInstance());
		if (Instance == nullptr)
		{
			UE_LOG(LogBlazingMoon, Error, TEXT("Could not get instance while attempting to save."));
			return;
		}
		Instance->SetPreviousLevel(UGameplayStatics::GetCurrentLevelName(this));
		const auto Save = Cast<UBlazingMoonSave>(UGameplayStatics::CreateSaveGameObject(UBlazingMoonSave::StaticClass()));
		Save->SaveGame(
			Instance->GetGameState(),
			Instance->GetPlayerState()
		);
		UGameplayStatics::SaveGameToSlot(Save, TEXT("SaveGame"), 0);
	}
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, LevelToLoad, false);
}
