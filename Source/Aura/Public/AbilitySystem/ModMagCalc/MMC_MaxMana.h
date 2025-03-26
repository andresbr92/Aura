// AndresD3v

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_MaxMana.generated.h"

/**
 * 
 * 1. Constructor
 * 2.  Override Main function CalculateBaseMagnitude_Implementation
 * 3. Declare a variable to capture the attribute we want
 * 4. Capture the attribute that max health depends on and set the source and snapshot
 * 5. Add the VigorDef to the array of attributes to capture.
 * 6. (optional) capture all tags
 * 7. Create de EvaluationParameters and set his tags.
 * 8. Call the function to capture the attribute magnitude. We define a float value first and the function
     * will set this float value passed as a parameter
 * 9.  We can capture de source UObject from the Spec. This will be the character in this case, so we
	 * can Cast to the CombatInterface
	 * Calculate the max health based on the formula
 */
UCLASS()
class AURA_API UMMC_MaxMana : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	UMMC_MaxMana();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

	FGameplayEffectAttributeCaptureDefinition IntelligenceDef;
	
};
