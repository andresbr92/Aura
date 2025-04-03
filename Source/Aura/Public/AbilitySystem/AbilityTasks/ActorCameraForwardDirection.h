// AndresD3v

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "ActorCameraForwardDirection.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FActorCameraForwardVectorSignature, const FVector&, ForwardVector);
UCLASS()
class AURA_API UActorCameraForwardDirection : public UAbilityTask
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category= "Ability|Tasks", meta=(DisplayName = "ActorCameraForwardDirection", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly))
	static UActorCameraForwardDirection* GetActorCameraForwardDirection(UGameplayAbility* OwningAbility);

	UPROPERTY(BlueprintAssignable)
	FActorCameraForwardVectorSignature CameraForwardVectorDelegate;

private:
	virtual void Activate() override;
};
