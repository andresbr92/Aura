// AndresD3v

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interaction/CombatInterface.h"
#include "AuraCharacterBase.generated.h"

class UGameplayAbility;
class UGameplayEffect;
class UAttributeSet;
class UAbilitySystemComponent;

UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:

	AAuraCharacterBase();
	// IAbilitySystemInterface Override
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }
	// UFUNCTION()
	// virtual FVector GetCombatSocketLocation() override;

	UPROPERTY(EditDefaultsOnly, Category= "Combat")
	TObjectPtr<UAnimMontage> HitAnimMontage;

	
	virtual UAnimMontage* GetHitReactMontage_Implementation() override;

protected:

	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = "Combat", BlueprintReadOnly)
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY(EditAnywhere, Category = "Combat")
	FName WeaponTipSocketName;
	

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(EditAnywhere, Category= "Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;
	UPROPERTY(EditAnywhere, Category= "Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;
	UPROPERTY(EditAnywhere, Category= "Attributes")
	TSubclassOf<UGameplayEffect> VitalAttributes;

	
	virtual void InitializeDefaultAttributes() const;


	UPROPERTY(EditAnywhere, Category= "Abilties")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
	
	virtual void GrantStartupAbilities();

	virtual void InitAbilityActorInfo();
private:
	void ApplyGameplayEffectAttributes(TSubclassOf<UGameplayEffect> GameplayEffectToApply, float Level) const;

	
	
	
};
