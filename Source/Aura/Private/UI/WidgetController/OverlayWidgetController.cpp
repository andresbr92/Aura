// AndresD3v


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet);
	
	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());
	
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet);
	// Bind Health replace with lambda
	 AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		}
	);
	
	// Bind MaxHealth replace with lambda
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxMaxHealthChanged.Broadcast(Data.NewValue);
		}
	);

	// Bind Mana replace with lambda
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);
		}
	);

	// Bind MaxMana replace with lambda
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxManaChanged.Broadcast(Data.NewValue);
		}
	);

	// Bind Asset Tags
	UAuraAbilitySystemComponent* AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	AuraAbilitySystemComponent->OnEffectAssetTags.AddUObject(this, &UOverlayWidgetController::OnAssetTagReceivedFromGE);
	
	// Lambda for message delegates
	AuraAbilitySystemComponent->OnEffectAssetTags.AddLambda(
		// [this] is the capture list, in the case of this lambda, we want to capture this (OverlayWidgetController)
		[this](const FGameplayTagContainer& AssetTags)
	{
		for (const auto& Tag : AssetTags)
		{
			// Declare the tag we want to check. In our case "MessageTag"
			FGameplayTag ParentMessageGameplayTag = FGameplayTag::RequestGameplayTag(FName("Message"));
			if (Tag.MatchesTag(ParentMessageGameplayTag))
			{
				
					
				const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
				OnMessageWidgetRow.Broadcast(*Row);
				
			}
			
		}
	});
	
}

void UOverlayWidgetController::OnAssetTagReceivedFromGE(const FGameplayTagContainer& TagContainer) const
{
	
}

// void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
// {
// 	OnHealthChanged.Broadcast(Data.NewValue);
// }
//
// void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
// {
// 	OnMaxMaxHealthChanged.Broadcast(Data.NewValue);
// }
// void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
// {
// 	OnManaChanged.Broadcast(Data.NewValue);
// }
//
// void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
// {
// 	OnMaxManaChanged.Broadcast(Data.NewValue);
// }
