// AndresD3v


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "AbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Aura/Aura.h"
#pragma optimize("", off)
struct AuraDamageStatics
{
	// What it does: Creates an FGameplayEffectAttributeCaptureDefinition named AttributeNameDef (e.g., ArmorDef)
	// and an FProperty* named AttributeNameProperty (e.g., ArmorProperty) within the struct.
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	AuraDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, BlockChance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, ArmorPenetration, Source, false);
	}
	
};
static const AuraDamageStatics& GetAuraDamageStatics()
{
	static AuraDamageStatics DStatics = AuraDamageStatics();
	return DStatics;
}

UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(GetAuraDamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(GetAuraDamageStatics().BlockChanceDef);
	RelevantAttributesToCapture.Add(GetAuraDamageStatics().ArmorPenetrationDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                              FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	// ExecutionParams.s
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
 	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	const AActor* SourceAvatarActor = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	const AActor* TargetAvatarActor = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	FGameplayEffectSpec EffectSpec = ExecutionParams.GetOwningSpec();
	const FGameplayTagContainer* SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();
	
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	// Base Damage
	float Damage = EffectSpec.GetSetByCallerMagnitude(FAuraGameplayTags::Get().Damage);
	// Calculate Block Chance
	float TargetBlockChance;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetAuraDamageStatics().BlockChanceDef, EvaluationParameters, TargetBlockChance);
	TargetBlockChance = FMath::Max<float>(0.f, TargetBlockChance);
	bool bBlocked = FMath::RandRange(0, 100) < TargetBlockChance;
	Damage = bBlocked && Damage /2.f;
	
	float TargetArmor = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetAuraDamageStatics().ArmorDef, EvaluationParameters,TargetArmor);
	TargetArmor = FMath::Max<float>(0.f, TargetArmor);
	// Calculate damage after armor
	
	
	

	// Calculate armor penetration
	float SourceArmorPenetration;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetAuraDamageStatics().ArmorPenetrationDef, EvaluationParameters, SourceArmorPenetration);
	SourceArmorPenetration = FMath::Max<float>(0.f, SourceArmorPenetration);
	CONSOLE_LOG("Aura Armor Penetration: %f", SourceArmorPenetration);
	const float EffectiveArmor = TargetArmor += (100 - SourceArmorPenetration * 0.25f) / 100.f;

	Damage *= (100.f - EffectiveArmor) / 100.f;
	

	// Calculate Armor
	
	
	FGameplayModifierEvaluatedData EvaluatedData(UAuraAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
