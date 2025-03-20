// AndresD3v

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetWidgetController(UObject* InWidgetController);
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;
protected:
	// Begin play like function! This function is called in BLUEPRINTS when the widget controller is set
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};
