
#include "AuraAbilityTypes.h"

bool FAuraGameplayEffectContext::NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
{
	return FGameplayEffectContext::NetSerialize(Ar, Map, bOutSuccess);
}

FGameplayEffectContext* FAuraGameplayEffectContext::Duplicate() const
{
	return FGameplayEffectContext::Duplicate();
}
