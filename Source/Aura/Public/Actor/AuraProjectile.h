// AndresD3v

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "AuraProjectile.generated.h"

class UNiagaraSystem;
class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class AURA_API AAuraProjectile : public AActor
{
	GENERATED_BODY()
	
public:	

	AAuraProjectile();
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;
	UPROPERTY(EditAnywhere, Category="Projectile Propperties")
	float InitialSpeed = 1100.f;
	UPROPERTY(EditAnywhere, Category="Projectile Propperties")
	float MaxSpeed = 1100.f;
	UPROPERTY(EditAnywhere, Category="Projectile Propperties")
	float ProjectileGravityScale = 0.2f;

protected:
	
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	
	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraSystem> ImpactEffect;
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> ImpactSound;
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> LoopSound;
	UPROPERTY()
	TObjectPtr<UAudioComponent> LoopSoundComponent;
	
	UPROPERTY(BlueprintReadWrite, meta=(ExposeOnSpawn = true))
	FGameplayEffectSpecHandle DamageEffectSpecHandle;
private:
	float lifeSpan = 10.f;
    /** 
     * Flag to track if impact effects have been played on clients
     * True: Effects already played during overlap
     * False: Effects need to be played during destruction
     * 
     * This flag is used to handle network replication of impact effects:
     * - On server: Projectile is destroyed and replicates to clients
     * - On clients: 
     *   - If hit detected locally, effects play on overlap (bHit = true)
     *   - If no local hit, effects play on destruction (bHit = false)
     * 
     * This prevents both double-playing and missing effects across the network
     */
    bool bHit = false;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;
	

};
