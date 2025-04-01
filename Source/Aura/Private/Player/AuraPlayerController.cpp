// AndresD3v


#include "Player/AuraPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Input/AuraInputComponent.h"
#include "Interaction/EnemyInterface.h"
#include "Components/SplineComponent.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "AuraGameplayTags.h"
#include "Player/AuraPlayerState.h"
#include "Character/AuraCharacter.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
	// Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
	
	// Rotar el personaje hacia la posición del cursor si es un AuraCharacter
	if (AAuraCharacter* AuraChar = Cast<AAuraCharacter>(GetPawn()))
	{
		if (CursorHit.bBlockingHit)
		{
			AuraChar->RotateTowardsMouse(CursorHit.ImpactPoint);
		}
	}
}
// void AAuraPlayerController::AutoRun()
// {
// 	if (!bAutoRunning) return;
// 	if (APawn* ControlledPawn = GetPawn())
// 	{
// 		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
// 		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline, ESplineCoordinateSpace::World);
// 		ControlledPawn->AddMovementInput(Direction);
//
// 		const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();
// 		if (DistanceToDestination <= AutoRunAcceptanceRadius)
// 		{
// 			bAutoRunning = false;
// 		}
// 	}
// }
void AAuraPlayerController::CursorTrace()
{
	
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	// We cast to the interface of the actor that was hit. But since we're using TScriptInterface, it's not necessary
	// ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());
	LastActor = ThisActor;
	ThisActor = CursorHit.GetActor();

	/**
	 * Line trace from cursor. There are several scenarios:
	 *  A. LastActor is null && ThisActor is null
	 *		- Do nothing
	 *	B. LastActor is null && ThisActor is valid
	 *		- Highlight ThisActor
	 *	C. LastActor is valid && ThisActor is null
	 *		- UnHighlight LastActor
	 *	D. Both actors are valid, but LastActor != ThisActor
	 *		- UnHighlight LastActor, and Highlight ThisActor
	 *	E. Both actors are valid, and are the same actor
	 *		- Do nothing
	 */
	if (LastActor != ThisActor)
	{
		if (LastActor) LastActor->UnHighlightActor();
		if (ThisActor) ThisActor->HighlightActor();
	}
	
}

void AAuraPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	// if (InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	// {
	// 	bTargeting = ThisActor ? true : false;
	// 	bAutoRunning = false;
	// }
}

void AAuraPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (GetASC())
	{
		GetASC()->AbilityInputTagReleased(InputTag);
	}
	// AUTORUN IMPLEMENTATION
	// if (!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	// {
	// 	if (GetASC())
	// 	{
	// 		GetASC()->AbilityInputTagReleased(InputTag);
	// 	}
	// 	return;
	// }

	// if (bTargeting)
	
	
	// else
	// {
	// 	APawn* ControlledPawn = GetPawn();
	// 	if (FollowTime <= ShortPressThreshold && ControlledPawn)
	// 	{
	// 		if (UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, ControlledPawn->GetActorLocation(), CachedDestination))
	// 		{
	// 			Spline->ClearSplinePoints();
	// 			for (const FVector& PointLoc : NavPath->PathPoints)
	// 			{
	// 				Spline->AddSplinePoint(PointLoc, ESplineCoordinateSpace::World);
	// 				DrawDebugSphere(GetWorld(), PointLoc, 8.f, 8, FColor::Green, false, 5.f);
	// 			}
	// 			// CachedDestination = NavPath->PathPoints[NavPath->PathPoints.Num() - 1];
	// 			// bAutoRunning = true;
	// 		}
	// 	}
	// 	FollowTime = 0.f;
	// 	bTargeting = false;
	// }
}

void AAuraPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (GetASC())
	{
		GetASC()->AbilityInputTagHeld(InputTag);
	}
	// if (!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	// {
	// 	if (GetASC())
	// 	{
	// 		GetASC()->AbilityInputTagHeld(InputTag);
	// 	}
	// 	return;
	// }

	// if (bTargeting)
	// {
	
	// else
	// {
	// 	FollowTime += GetWorld()->GetDeltaSeconds();
	//
	// 	FHitResult Hit;
	// 	if (GetHitResultUnderCursor(ECC_Visibility, false, Hit))
	// 	{
	// 		CachedDestination = Hit.ImpactPoint;
	// 	}
	//
	// 	if (APawn* ControlledPawn = GetPawn())
	// 	{
	// 		const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
	// 		ControlledPawn->AddMovementInput(WorldDirection);
	// 	}
	// }
	// if (GetASC() == nullptr) return;
	// GetASC()->AbilityInputTagHeld(InputTag);
}
UAuraAbilitySystemComponent* AAuraPlayerController::GetASC()
{
	if (AuraAbilitySystemComponent == nullptr)
	{
		AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return AuraAbilitySystemComponent;
}



void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(AuraContext,0);
	}

	// Enable mouse cursor visibility on screen
	bShowMouseCursor = true;
	// Set the default system cursor
	DefaultMouseCursor = EMouseCursor::Default;

	// Configure input mode to allow both game controls and UI interaction
	FInputModeGameAndUI InputModeData;
	// Prevent cursor from being locked to the game window
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	// Keep cursor visible during input capture
	InputModeData.SetHideCursorDuringCapture(false);
	// Apply input mode configuration
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UAuraInputComponent* AuraInputComponent = CastChecked<UAuraInputComponent>(InputComponent);

	AuraInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
	AuraInputComponent->BindAbilityActions(AuraInputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}
