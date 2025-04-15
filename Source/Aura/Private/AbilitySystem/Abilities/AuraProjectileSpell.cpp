// AndresD3v


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/KismetSystemLibrary.h"

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	
	
}

void UAuraProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation, FVector ProjectileSpawnLocation, const FGameplayTag& SocketTag,
	bool bOverridePitch, float PitchOverride)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;
 
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (CombatInterface)
	{

		
		FRotator Rotation = (ProjectileTargetLocation - ProjectileSpawnLocation).Rotation();
		Rotation.Pitch = 0.f;
 
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(ProjectileSpawnLocation);
		SpawnTransform.SetRotation(Rotation.Quaternion());
		
 
		
		
 
		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		// todo: GE
		UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
		FGameplayEffectContextHandle ContextHandle = SourceASC->MakeEffectContext();
		ContextHandle.AddSourceObject(this);
		FGameplayEffectSpecHandle EffectSpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, 1.f, ContextHandle);
		
		FAuraGameplayTags AuraGameplayTags = FAuraGameplayTags::Get();
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(EffectSpecHandle, AuraGameplayTags.Damage, 50.f);
		
		Projectile->DamageEffectSpecHandle = EffectSpecHandle;
		
		Projectile->FinishSpawning(SpawnTransform);
	}
}

float UAuraProjectileSpell::GetDamageByAbilityLevel(float AbilityLevel) const
{
	return Damage.GetValueAtLevel(AbilityLevel);
}
