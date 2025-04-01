// AndresD3v

#pragma once

#include "CoreMinimal.h"
#include "AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

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

	// Rotates the character to face the direction of the mouse cursor
	void RotateTowardsMouse(const FVector& CursorLocation);

private:
	virtual void InitAbilityActorInfo() override;

	// Velocidad a la que el personaje rota hacia el cursor
	UPROPERTY(EditDefaultsOnly, Category = "Character Movement")
	float RotationSpeed = 10.0f;
};
