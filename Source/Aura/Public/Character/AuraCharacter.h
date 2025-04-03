// AndresD3v

#pragma once

#include "CoreMinimal.h"
#include "AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

class UCameraComponent;

UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAuraCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	/** Combat Interface */
	virtual int32 GetPlayerLevel() override;
	/** end Combat Interface */
	

	// virtual FVector GetCameraForwardVector() override;
	// virtual void SetFacingTarget() override;


private:
	virtual void InitAbilityActorInfo() override;

	
};
