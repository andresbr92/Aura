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
	
	// AuraAS->GetStrength()
	// Broadcast Strength
	FAuraAttributeInfo StrengthAttributeInfo = AttributeInfo->GetAttributeInfoByGameplayTag(FAuraGameplayTags::Get().Attributes_Primary_Strength, false);
	StrengthAttributeInfo.AttributeValue = AuraAS->GetStrength();

	AttributeInfoDelegate.Broadcast(StrengthAttributeInfo);
	
	
	
}
