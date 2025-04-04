// AndresD3v


#include "AbilitySystem/AbilityTasks/ActorCameraForwardDirection.h"

#include "Camera/CameraComponent.h"
#include "Character/AuraCharacter.h"
#include "GameFramework/Character.h"

UActorCameraForwardDirection* UActorCameraForwardDirection::GetActorCameraForwardDirection(
	UGameplayAbility* OwningAbility)
{
	UActorCameraForwardDirection* MyObj = NewAbilityTask<UActorCameraForwardDirection>(OwningAbility);
	return MyObj;
}

void UActorCameraForwardDirection::Activate()
{
	
	// ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActor());
	//
	// CameraForwardVectorDelegate.Broadcast(CombatInterface->GetCameraForwardVector());
	
}
