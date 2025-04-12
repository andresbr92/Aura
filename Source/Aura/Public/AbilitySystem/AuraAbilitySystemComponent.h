// AndresD3v

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"

#include "AuraAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags,const FGameplayTagContainer& /* Asset tags that the GE have*/)
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AURA_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	void AbilityActorInfoHaveBeenSet();


	// Delegate to broadcast gameplayTags from asset (GE's)
	FEffectAssetTags OnEffectAssetTags;

	/**
	 * Grants the startup abilities to the player.
	 * @param AbilitiesToGrant: The abilities to grant to the player.
	 * @note Also, this function store the handles of the abilities in the GrantedAbilities array. For each ability, we store the StartupInputTag in the AbilitySpec for later activation.
	 */
	void GrantStartupAbilities(const TArray<TSubclassOf<UGameplayAbility>>& AbilitiesToGrant);

	void AbilityInputTagHeld(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);

	TArray<FGameplayAbilitySpecHandle> GrantedAbilities;
protected:
	UFUNCTION(Client, Reliable)
	void ClientEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
	
	
	
};
