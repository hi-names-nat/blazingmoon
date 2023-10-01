// (c) Dark Frog SGS 2023.
#include "DamageTypeTrigger.h"

void UDamageTypeTrigger::DamageObject(float amount, UDamageType* DamageType)
{
	if (DamageType->GetName() == ExpectedDamageType->GetName())
	{
		OnCorrectDamage.Broadcast();
	}
}
