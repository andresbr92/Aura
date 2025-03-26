// AndresD3v

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_MaxHealth.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UMMC_MaxHealth : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
	// Step 1. Constructor
	UMMC_MaxHealth();

	// Step 2. Override Main function CalculateBaseMagnitude_Implementation
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

	// Step 3. Declare a variable to capture the attribute we want
	FGameplayEffectAttributeCaptureDefinition VigorDef;
	
};
