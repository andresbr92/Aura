// AndresD3v


#include "Player/AuraPlayerController.h"

#include "EnhancedInputSubsystems.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(AuraContext,0);

	// Habilita la visibilidad del cursor del mouse en la pantalla
	bShowMouseCursor = true;
	// Establece el cursor predeterminado del sistema
	DefaultMouseCursor = EMouseCursor::Default;

	// Configura el modo de entrada para permitir tanto controles de juego como interfaz de usuario
	FInputModeGameAndUI InputModeData;
	// Evita que el cursor se bloquee dentro de la ventana del juego
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	// Mantiene el cursor visible durante la captura de entrada
	InputModeData.SetHideCursorDuringCapture(false);
	
	SetInputMode(InputModeData);
}
