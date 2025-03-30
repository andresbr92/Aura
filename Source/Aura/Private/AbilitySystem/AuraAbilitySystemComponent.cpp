// AndresD3v


#include "AbilitySystem/AuraAbilitySystemComponent.h"

#include "AuraGameplayTags.h"


void UAuraAbilitySystemComponent::AbilityActorInfoHaveBeenSet()
{
	// We use this function to bind all functions to the ASC delegates
	// OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);
	OnGameplayEffectAppliedDelegateToTarget.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);

	const FAuraGameplayTags& AuraGameplayTags = FAuraGameplayTags::Get();
	
}

void UAuraAbilitySystemComponent::GrantStartupAbilities(const TArray<TSubclassOf<UGameplayAbility>> AbilitiesToGrant)
{
	if (!AbilitiesToGrant.IsEmpty())
	{
		for (auto Ability: AbilitiesToGrant)
		{
			// FGameplayAbilitySpec(TSubclassOf<UGameplayAbility> InAbilityClass, int32 InLevel = 1, int32 InInputID = INDEX_NONE, UObject* InSourceObject = nullptr);
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability, 1);
			AbilitySpec.SourceObject = this;
			FGameplayAbilitySpecHandle AbilitySpecHandle = GiveAbility(AbilitySpec);
			GrantedAbilities.Add(AbilitySpecHandle);
		}
	}
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
                                                const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{

	// print all asset tags
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	OnEffectAssetTags.Broadcast(TagContainer);
}
