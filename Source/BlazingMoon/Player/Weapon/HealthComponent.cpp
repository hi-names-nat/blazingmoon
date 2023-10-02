// (c) Dark Frog SGS 2023.


#include "HealthComponent.h"
#include "BlazingMoon/BlazingMoon.h"


void UHealthComponent::TakeDamage(float Amount)
{
	UE_LOG(LogBlazingMoon, Log, TEXT("Took Damage. Current Health: %d"), CurrentHealth);
	CurrentHealth = CurrentHealth - Amount;
	UE_LOG(LogBlazingMoon, Log, TEXT("Took Damage. New Health: %d"), CurrentHealth);
	if (CurrentHealth <= 0)
	{
		UE_LOG(LogBlazingMoon, Log, TEXT("Die"));
		OnKilled.Broadcast();
	}
	else
	{
		OnHurt.Broadcast();
	}
}

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	UPrimitiveComponent::SetCollisionProfileName("BlockAll");
	CurrentHealth = MaxHealth;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	CurrentHealth = MaxHealth;
}
