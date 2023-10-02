// (c) Dark Frog SGS 2023.
#include "DamageTypeTrigger.h"

void UDamageTypeTrigger::DamageObject(float amount, bool isFire)
{
	if (isFire)
	{
		UE_LOG(LogTemp, Log, TEXT("AJGJAS"))
		OnCorrectDamage.Broadcast();
	}
}
