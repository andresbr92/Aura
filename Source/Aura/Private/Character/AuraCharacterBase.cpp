// AndresD3v


#include "Character/AuraCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Player/AuraPlayerState.h"

// Sets default values
AAuraCharacterBase::AAuraCharacterBase()
{
 	
	PrimaryActorTick.bCanEverTick = false;
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


// FVector AAuraCharacterBase::GetCombatSocketLocation()
// {
// 	check(Weapon)
// 	return Weapon->GetSocketLocation(WeaponTipSocketName);
// }

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraCharacterBase::ApplyGameplayEffectAttributes(TSubclassOf<UGameplayEffect> GameplayEffectToApply, float Level) const
{
	check(DefaultPrimaryAttributes)
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	if (ASC)
	{
		FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
		ContextHandle.AddSourceObject(this);

		FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(GameplayEffectToApply, Level, ContextHandle);

		ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		
	}
}


void AAuraCharacterBase::InitializeDefaultAttributes() const
{
}

void AAuraCharacterBase::GrantStartupAbilities()
{
	
	// Return if we ARE NOT the server
	if (!HasAuthority()) return;
	UAuraAbilitySystemComponent* AuraASC = Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	AuraASC->GrantStartupAbilities(StartupAbilities);
	
}


void AAuraCharacterBase::InitAbilityActorInfo()
{
}



