// AndresD3v

#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

// Sets default values
AAuraCharacter::AAuraCharacter()
{
    // Deshabilitamos la rotación automática hacia el movimiento para permitir nuestra rotación personalizada
    GetCharacterMovement()->bOrientRotationToMovement = false;
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

void AAuraCharacter::PossessedBy(AController *NewController)
{
    Super::PossessedBy(NewController);
    // Init ability actor info for the Server
    InitAbilityActorInfo();
    
    GrantStartupAbilities();
}

void AAuraCharacter::OnRep_PlayerState()
{
    Super::OnRep_PlayerState();
    // Init ability actor info for the Client
    InitAbilityActorInfo();
}

int32 AAuraCharacter::GetPlayerLevel()
{
    const AAuraPlayerState *AuraPlayerState = GetPlayerState<AAuraPlayerState>();
    check(AuraPlayerState);
    return AuraPlayerState->GetPlayerLevel();
}

void AAuraCharacter::RotateTowardsMouse(const FVector& CursorLocation)
{
    // Calcular la dirección desde el personaje hacia el cursor
    FVector Direction = CursorLocation - GetActorLocation();
    // Ignoramos la altura (eje Z) para mantener la rotación en el plano XY
    Direction.Z = 0.0f;
    Direction = Direction.GetSafeNormal();

    if (Direction.IsNearlyZero())
    {
        return;
    }

    // Convertir la dirección a una rotación (solo en el eje Yaw)
    FRotator TargetRotation = Direction.Rotation();
    // Solo queremos aplicar la rotación en el eje Yaw (horizontal)
    TargetRotation.Pitch = 0.0f;
    TargetRotation.Roll = 0.0f;

    // Aplicar la rotación con suavizado
    FRotator CurrentRotation = GetActorRotation();
    FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, GetWorld()->GetDeltaSeconds(), RotationSpeed);
    
    // Establecer la rotación del personaje
    SetActorRotation(NewRotation);
}

void AAuraCharacter::InitAbilityActorInfo()
{
    Super::InitAbilityActorInfo();
    AAuraPlayerState *AuraPlayerState = GetPlayerState<AAuraPlayerState>();
    check(AuraPlayerState);
    AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState, this);
    
    AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
    
    // We call this function after de ability actor info to bind al functions to the ASC delegates
    Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoHaveBeenSet();
    AttributeSet = AuraPlayerState->GetAttributeSet();

    /*
     * Here we initialize the Overlay because we have all the data we need: the player controller, player state, ability system component and attribute set.
     * Also, the HUD is accessible from the player controller.
     */
    

    if (AAuraPlayerController *AuraPlayerController = Cast<AAuraPlayerController>(GetController()))
    {

        AHUD *AHUD = AuraPlayerController->GetHUD();

        if (AAuraHUD *AuraHUD = Cast<AAuraHUD>(AHUD))
        {
            AuraHUD->InitOverlay(AuraPlayerController, AuraPlayerState, AbilitySystemComponent, AttributeSet);
        }
    }
    // We can call this ONLY in the server because attributes is marked as replicated. But is ok doing it here.
    InitializeDefaultAttributes();

    //
   
    
}
