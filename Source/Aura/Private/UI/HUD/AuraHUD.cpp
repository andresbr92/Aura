// AndresD3v


#include "UI/HUD/AuraHUD.h"

#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "UI/Widgets/AuraUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		OverlayWidgetController->BindCallbacksToDependencies();
		
	}
	return OverlayWidgetController;
}

UAttributeMenuWidgetController* AAuraHUD::GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams)
{
	if (AttributeMenuWidgetController == nullptr)
	{
		AttributeMenuWidgetController = NewObject<UAttributeMenuWidgetController>(this, AttributeMenuWidgetControllerClass);
		AttributeMenuWidgetController->SetWidgetControllerParams(WCParams);
		AttributeMenuWidgetController->BindCallbacksToDependencies();
		
	}
	return AttributeMenuWidgetController;

}

/*
* =================================================================================================
* Widget Controllers System - Architecture and Flow
* =================================================================================================
*
* General Structure:
* ------------------
*     AuraHUD -----> AuraUserWidget -----> WidgetController
*        |                |                      |
*        |                |                      |
*        +----------------+----------------------+
*                        |
*                  FWidgetControllerParams
*
* Components:
* -----------
* 1. FWidgetControllerParams:
*    - Container for essential data (PC, PS, ASC, AS)
*    - Allows passing all references in a single structure
*
* 2. AuraUserWidget:
*    - Base class for all UI widgets
*    - Connects UI with Controller
*    - Provides:
*      > SetWidgetController(): Assigns the controller
*      > WidgetControllerSet(): Blueprint event triggered when controller is ready
*
* 3. WidgetController:
*    - Handles business logic
*    - Maintains references to game components
*    - Acts as bridge between game and UI
*
* 4. AuraHUD:
*    - Orchestrates creation and setup
*    - Manages Widget and Controller lifecycle
*
* Initialization Flow:
* -------------------
* 1. InitOverlay() [AuraHUD]
*    |
*    +--> Creates Widget
*    |
*    +--> Prepares FWidgetControllerParams
*    |
*    +--> GetOverlayWidgetController()
*    |    |
*    |    +--> Creates Controller if it doesn't exist
*    |    +--> Configures Controller with params
*    |
*    +--> Widget->SetWidgetController()
*         |
*         +--> Assigns Controller
*         +--> Triggers WidgetControllerSet() in Blueprint
*
* Benefits:
* ---------
* - Clear separation of responsibilities (MVC)
* - Easy to extend and maintain
* - Logic reusability
* - Natural Blueprint integration
*/

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, please fill out BP_AuraHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitialized, please fill out BP_AuraHUD"));
	
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UAuraUserWidget>(Widget);

	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();
	
	
	Widget->AddToViewport();
}
