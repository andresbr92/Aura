// AndresD3v

#pragma once

#include "CoreMinimal.h"
#include "AuraCharacterBase.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"
class UWidgetComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyAttributeChangedSignature, float, AttributeValue);
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

	
	/** Combat Interface */
	virtual int32 GetPlayerLevel() override;
	/** end Combat Interface */

	// Enemy is his own widgetController
	void BroadCastInitialValues();
	void BindCallbacksToDependencies();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

protected:
	virtual void InitAbilityActorInfo() override;
	virtual void InitializeDefaultAttributes() const override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Class Default")
	int32 Level = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Class Default")
	ECharacterClass CharacterClass = ECharacterClass::Warrior;
	
	UPROPERTY(BlueprintAssignable)
	FOnEnemyAttributeChangedSignature OnHealthChange;
	
	UPROPERTY(BlueprintAssignable)
	FOnEnemyAttributeChangedSignature OnMaxHealthChange;

	
};
