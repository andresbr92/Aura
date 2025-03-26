// AndresD3v


#include "AbilitySystem/ModMagCalc/MMC_MaxHealth.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	//Step 4. Capture the attribute that max health depends on and set the source and snapshot
	VigorDef.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute();
	VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	VigorDef.bSnapshot = false;

	//Step 5. Add the VigorDef to the array of attributes to capture.
	RelevantAttributesToCapture.Add(VigorDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Step 6. (optional) capture all tags
	// For future applications, we can capture the tags of the source and the target via effectSpec
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	// Step 6. Create de EvaluationParameters and set his tags.
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;
	/*
	* Step 7. Call the function to capture the attribute magnitude. We define a float value first and the function
	* will set this float value passed as a parameter
	*/
	float Vigor = 0.f;
	GetCapturedAttributeMagnitude(VigorDef, Spec, EvaluationParameters, Vigor);
	// Just in case, we clamp the value of vigor from negative value to 0
	Vigor = FMath::Max<float>(Vigor, 0.0f);

	/*
	 * We can capture de source UObject from the Spec. This will be the character in this case, so we
	 * can Cast to the CombatInterface
	 */
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();

	// Step 8. Calculate the max health based on the formula
	return 80.f + 2.5f * Vigor + 10.f * PlayerLevel;
	
}
