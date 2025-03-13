// AndresD3v


#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerState.h"


// Sets default values
AAuraCharacter::AAuraCharacter()
{
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
    GetCharacterMovement()->bConstrainToPlane = true;
    GetCharacterMovement()->bSnapToPlaneAtStart = true;


    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;
    
}
    /** 
     * REMEMBER: Called when this Pawn is possessed. Only called on the server (or in standalone).
     */

void AAuraCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);
    // Init ability actor info for the Server
    InitAbilityActorInfo();

    
}

void AAuraCharacter::OnRep_PlayerState()
{
    Super::OnRep_PlayerState();
    // Init ability actor info for the Client
    InitAbilityActorInfo();
    
}

void AAuraCharacter::InitAbilityActorInfo()
{
    AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
    check(AuraPlayerState);
    AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState, this);
    AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
    AttributeSet = AuraPlayerState->GetAttributeSet();
    
}


