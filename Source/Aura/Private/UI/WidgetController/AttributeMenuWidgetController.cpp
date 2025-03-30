// AndresD3v


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UAuraAttributeSet * AuraAS = CastChecked<UAuraAttributeSet>(AttributeSet);
	check(AttributeInfo);

	for (auto Pair: AuraAS->TagsToAttributes)
	{
		FAuraAttributeInfo Info = AttributeInfo->GetAttributeInfoByGameplayTag(Pair.Key);
		Info.AttributeValue = Pair.Value().GetNumericValue(AuraAS);
		AttributeInfoDelegate.Broadcast(Info);
	}
	
	
	
	// OLD MODE
	// FAuraAttributeInfo StrengthAttributeInfo = AttributeInfo->GetAttributeInfoByGameplayTag(FAuraGameplayTags::Get().Attributes_Primary_Strength, false);
	// StrengthAttributeInfo.AttributeValue = AuraAS->GetStrength();
	// AttributeInfoDelegate.Broadcast(StrengthAttributeInfo);
	//
	// // Broadcast Intelligence
	// FAuraAttributeInfo IntelligenceAttributeInfo = AttributeInfo->GetAttributeInfoByGameplayTag(FAuraGameplayTags::Get().Attributes_Primary_Intelligence, false);
	// IntelligenceAttributeInfo.AttributeValue = AuraAS->GetIntelligence();
	// AttributeInfoDelegate.Broadcast(IntelligenceAttributeInfo);
	//
	// // Broadcast Resilience
	// FAuraAttributeInfo ResilienceAttributeInfo = AttributeInfo->GetAttributeInfoByGameplayTag(FAuraGameplayTags::Get().Attributes_Primary_Resilience, false);
	// ResilienceAttributeInfo.AttributeValue = AuraAS->GetResilience();
	// AttributeInfoDelegate.Broadcast(ResilienceAttributeInfo);
	//
	// // Broadcast Vigor
	// FAuraAttributeInfo VigorAttributeInfo = AttributeInfo->GetAttributeInfoByGameplayTag(FAuraGameplayTags::Get().Attributes_Primary_Vigor, false);
	// VigorAttributeInfo.AttributeValue = AuraAS->GetVigor();
	// AttributeInfoDelegate.Broadcast(VigorAttributeInfo);

	
	// FAuraAttributeInfo ArmorAttributeInfo = AttributeInfo->GetAttributeInfoByGameplayTag(FAuraGameplayTags::Get().Attributes_Secondary_Armor, false);
	// ArmorAttributeInfo.AttributeValue = AuraAS->GetArmor();
	// AttributeInfoDelegate.Broadcast(ArmorAttributeInfo);
	//
	// FAuraAttributeInfo ArmorPenetrationAttributeInfo = AttributeInfo->GetAttributeInfoByGameplayTag(FAuraGameplayTags::Get().Attributes_Secondary_ArmorPenetration, false);
	// ArmorPenetrationAttributeInfo.AttributeValue = AuraAS->GetArmorPenetration();
	// AttributeInfoDelegate.Broadcast(ArmorPenetrationAttributeInfo);
	//
	// FAuraAttributeInfo BlockChanceAttributeInfo = AttributeInfo->GetAttributeInfoByGameplayTag(FAuraGameplayTags::Get().Attributes_Secondary_BlockChance, false);
	// BlockChanceAttributeInfo.AttributeValue = AuraAS->GetBlockChance();
	// AttributeInfoDelegate.Broadcast(BlockChanceAttributeInfo);
	//
	// FAuraAttributeInfo CriticalHitChanceAttributeInfo = AttributeInfo->GetAttributeInfoByGameplayTag(FAuraGameplayTags::Get().Attributes_Secondary_CriticalHitChance, false);
	// CriticalHitChanceAttributeInfo.AttributeValue = AuraAS->GetCriticalHitChance();
	// AttributeInfoDelegate.Broadcast(CriticalHitChanceAttributeInfo);
	//
	// FAuraAttributeInfo CriticalHitDamageAttributeInfo = AttributeInfo->GetAttributeInfoByGameplayTag(FAuraGameplayTags::Get().Attributes_Secondary_CriticalHitDamage, false);
	// CriticalHitDamageAttributeInfo.AttributeValue = AuraAS->GetCriticalHitDamage();
	// AttributeInfoDelegate.Broadcast(CriticalHitDamageAttributeInfo);
	//
	// FAuraAttributeInfo CriticalHitResistanceAttributeInfo = AttributeInfo->GetAttributeInfoByGameplayTag(FAuraGameplayTags::Get().Attributes_Secondary_CriticalHitResistance, false);
	// CriticalHitResistanceAttributeInfo.AttributeValue = AuraAS->GetCriticalHitResistance();
	// AttributeInfoDelegate.Broadcast(CriticalHitResistanceAttributeInfo);
	//
	// FAuraAttributeInfo HealthRegenerationAttributeInfo = AttributeInfo->GetAttributeInfoByGameplayTag(FAuraGameplayTags::Get().Attributes_Secondary_HealthRegeneration, false);
	// HealthRegenerationAttributeInfo.AttributeValue = AuraAS->GetHealthRegeneration();
	// AttributeInfoDelegate.Broadcast(HealthRegenerationAttributeInfo);
	//
	// FAuraAttributeInfo ManaRegenerationAttributeInfo = AttributeInfo->GetAttributeInfoByGameplayTag(FAuraGameplayTags::Get().Attributes_Secondary_ManaRegeneration, false);
	// ManaRegenerationAttributeInfo.AttributeValue = AuraAS->GetManaRegeneration();
	// AttributeInfoDelegate.Broadcast(ManaRegenerationAttributeInfo);
	//
	// FAuraAttributeInfo MaxHealthAttributeInfo = AttributeInfo->GetAttributeInfoByGameplayTag(FAuraGameplayTags::Get().Attributes_Secondary_MaxHealth, false);
	// MaxHealthAttributeInfo.AttributeValue = AuraAS->GetMaxHealth();
	// AttributeInfoDelegate.Broadcast(MaxHealthAttributeInfo);
	//
	// FAuraAttributeInfo MaxManaAttributeInfo = AttributeInfo->GetAttributeInfoByGameplayTag(FAuraGameplayTags::Get().Attributes_Secondary_MaxMana, false);
	// MaxManaAttributeInfo.AttributeValue = AuraAS->GetMaxMana();
	// AttributeInfoDelegate.Broadcast(MaxManaAttributeInfo);
	





	
	
	
	
}
