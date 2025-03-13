// AndresD3v

#pragma once

#include "CoreMinimal.h"
#include "AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAuraEnemy();

	virtual void BeginPlay() override;

	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
};
