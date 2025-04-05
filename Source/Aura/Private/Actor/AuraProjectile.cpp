// AndresD3v


#include "Actor/AuraProjectile.h"


#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAuraProjectile::AAuraProjectile()
{
 
	PrimaryActorTick.bCanEverTick = false;
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	bReplicates = true;
	SetRootComponent(Sphere);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->InitialSpeed = InitialSpeed;
	ProjectileMovement->MaxSpeed = MaxSpeed;
	ProjectileMovement->ProjectileGravityScale = ProjectileGravityScale;
	
}


void AAuraProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(lifeSpan);
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraProjectile::OnSphereOverlap);

	LoopSoundComponent = UGameplayStatics::SpawnSoundAttached(LoopSound, GetRootComponent());
}

/**
 * Called when the projectile is being destroyed
 * Handles the replication of impact effects between server and clients
 * 
 * On clients:
 * - If bHit is false (no local hit detection), play effects here
 * - This ensures clients that missed the overlap event still see effects
 * - If bHit is true, skip effects as they were already played during overlap
 */
void AAuraProjectile::Destroyed()
{
	if (!HasAuthority() && !bHit)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());
		if (LoopSoundComponent)
		{
			LoopSoundComponent->Stop();
			
		}
	}
	Super::Destroyed();
}

/**
 * Handles projectile collision with other actors
 * Manages both the gameplay logic and visual/audio effects across the network
 * 
 * Network behavior:
 * - Server: Initiates destruction which replicates to all clients
 * - Clients: Play effects locally and set bHit flag to prevent double-playing
 * 
 * @param OverlappedComponent - The component that overlapped
 * @param OtherActor - The actor that we overlapped with
 * @param OtherComp - The component we overlapped with
 * @param OtherBodyIndex - The body index of the component we overlapped with
 * @param bFromSweep - Whether it was a sweeping motion
 * @param SweepResult - The hit result of the sweep
 */
void AAuraProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Play effects immediately on overlap detection for both server and clients
	UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());
	LoopSoundComponent->Stop();

	if (HasAuthority())
	{
		Destroy();
	} else
	{
		bHit = true;
	}
}



