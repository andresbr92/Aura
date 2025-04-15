#pragma once


#include "GameplayEffectTypes.h"
#include "AuraAbilityTypes.generated.h"

/**
 *@brief The GameplayEffectContext structure holds information about a GameplayEffectSpec's instigator and TargetData.
* Custom GameplayEffectContext for Aura. This is used to store additional data for the gameplay effect.
* the additional data is:
* - bIsCriticalHit: Whether the hit is a critical hit
* - bIsBlocked: Whether the hit is blocked
* @note To subclass the GameplayEffectContext:
* 1. Subclass FGameplayEffectContext
* 2. Override FGameplayEffectContext::Duplicate()
* 3. Override FGameplayEffectContext::NetSerialize() if your new data needs to be replicated
* 4. Implement TStructOpsTypeTraits for your subclass, like the parent struct FGameplayEffectContext has
* 5. Override AllocGameplayEffectContext() in your AbilitySystemGlobals class to return a new object of your subclass
*/
USTRUCT(BlueprintType)
struct FAuraGameplayEffectContext: public FGameplayEffectContext
{
	GENERATED_BODY()
public:
	bool IsCriticalHit() const { return bIsBlockedHit; };
	bool IsBlockedHit() const { return bIsBlockedHit; };

	void SetIsCriticalHit(bool bInIsCriticalHit) { bIsCriticalHit = bInIsCriticalHit; }
	void SetIsBlockedHit(bool bInIsBlockedHit) { bIsBlockedHit = bInIsBlockedHit; }


	
	virtual UScriptStruct* GetScriptStruct() const override
	{
		return StaticStruct();
	}
	virtual FAuraGameplayEffectContext* Duplicate() const override
	{
		FAuraGameplayEffectContext* NewContext = new FAuraGameplayEffectContext();
		*NewContext = *this;
		if (GetHitResult())
		{
			// Does a deep copy of the hit result
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}
	
	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess) override;


	
protected:
	UPROPERTY()
	bool bIsCriticalHit = false;
	UPROPERTY()
	bool bIsBlockedHit = false;

};

template <>
struct TStructOpsTypeTraits<FAuraGameplayEffectContext>: TStructOpsTypeTraitsBase2<FAuraGameplayEffectContext>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true
	};
};


