// AndresD3v


#include "AbilitySystem/AuraAttributeSet.h"


#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

UAuraAttributeSet::UAuraAttributeSet()
{
	InitHealth(50.f);
	InitMaxHealth(100.f);
	InitMana(25.f);
	InitMaxMana(100.f);
	
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Mana, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);

	// Primary Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resilience, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Vigor, COND_None, REPNOTIFY_Always);		
}
// OnRep functions of vital attributes

void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldHealth);
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealth, OldMaxHealth);
}
void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mana, OldMana);
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxMana, OldMaxMana);
}

// OnRep functions of primary attributes
void UAuraAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Strength, OldStrength);
}

void UAuraAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Intelligence, OldIntelligence);
}

void UAuraAttributeSet::OnRep_Resilience(const FGameplayAttributeData& OldResilience) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Resilience, OldResilience);
}

void UAuraAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldVigor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Vigor, OldVigor);
}

void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	// Clamp the health value
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}

	// Clamp the mana value
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
	
	
	
}



void UAuraAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	SetEffectProperties(Data);

	// Clamp again the health and mana values
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}

	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	}
}
	
/**
 * Called after a GameplayEffect is executed. This function is used to gather information about the effect's source
 * and target for further processing or reactions to the effect.
 * 
 * The function populates EffectProperties with data from the effect's context, which includes:
 * - ContextHandle: Contains the full context of the effect execution
 * - SourceASC: The AbilitySystemComponent of the actor that caused the effect
 * - SourceAvatarActor: The actual actor (usually character) that caused the effect
 * - SourceController: The player controller associated with the source actor
 * - SourceCharacter: The character pawn controlled by the source controller
 * 
 * This information is crucial for:
 * - Determining who caused the effect
 * - Accessing the source actor's attributes and abilities
 * - Handling player-specific logic
 * - Implementing reactions or consequences based on the effect source
 * 
 * Controller and Character Casting Scenarios:
 * 
 * 1. AI-Controlled Character:
 *    - SourceController will be nullptr initially
 *    - SourceAvatarActor will be the AI character (APawn)
 *    - We need to get the controller through Cast<APawn> to access the AIController
 *    Example: An AI enemy applying a damage effect to the player
 * 
 * 2. Player-Controlled Character:
 *    - SourceController will be available directly from AbilityActorInfo
 *    - We can directly cast to ACharacter since we know it's a player character
 *    Example: Player casting a healing spell on themselves
 * 
 * 3. Environmental Effect (No Controller):
 *    - SourceController will be nullptr
 *    - SourceAvatarActor might be nullptr or an environmental actor
 *    Example: A poison cloud area effect that damages all characters within range
 */
void UAuraAttributeSet::SetEffectProperties(const struct FGameplayEffectModCallbackData& Data)
{
	// Target is the thing is being affected (attribute set)
	// Source is the cause of the effect (in this case, effect actor)

	EffectProperties.ContextHandle = Data.EffectSpec.GetContext();
	
	// Get the AbilitySystemComponent of the actor that caused the effect
	EffectProperties.SourceASC = EffectProperties.ContextHandle.GetOriginalInstigatorAbilitySystemComponent();
	
	// Get the actual actor (usually character) that caused the effect
	EffectProperties.SourceAvatarActor = EffectProperties.SourceASC->AbilityActorInfo->AvatarActor.Get();
	
	// Get the player controller associated with the source actor
	EffectProperties.SourceController = EffectProperties.SourceASC->AbilityActorInfo->PlayerController.Get();
	
	// Case 1: Handle AI or environmental effects where controller isn't directly available
	// Example: AI enemy applying damage or environmental hazard affecting characters
	if (EffectProperties.SourceController == nullptr && EffectProperties.SourceAvatarActor != nullptr)
	{
		if (const APawn* Pawn = Cast<APawn>(EffectProperties.SourceAvatarActor))
		{
			EffectProperties.SourceController = Pawn->GetController();
		}
	}
	
	// Case 2: Handle player-controlled character effects
	// Example: Player casting spells or using abilities
	if (EffectProperties.SourceController)
	{
		EffectProperties.SourceCharacter = Cast<ACharacter>(EffectProperties.SourceController->GetPawn());
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		EffectProperties.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		EffectProperties.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		EffectProperties.TargetCharacter = Cast<ACharacter>(EffectProperties.TargetAvatarActor);
		EffectProperties.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(EffectProperties.TargetAvatarActor);
	}
}
