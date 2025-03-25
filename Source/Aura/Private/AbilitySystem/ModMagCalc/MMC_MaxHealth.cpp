// AndresD3v


#include "AbilitySystem/ModMagCalc/MMC_MaxHealth.h"

#include "AbilitySystem/AuraAttributeSet.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	//Step 4. Capture via UAuraAttributeSet
	VigorDef.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute();
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	return Super::CalculateBaseMagnitude_Implementation(Spec);
}
