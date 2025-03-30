// AndresD3v

#pragma once

#include "CoreMinimal.h"
#include "AuraWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

class UAttributeInfo;
struct FAuraAttributeInfo;
/**
 * @brief Delegate for the attribute info.
 * @param Info The FAttributeInfo to broadcast.
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FAuraAttributeInfo&, Info);

/**
 * @brief Widget controller for the attribute menu.
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_API UAttributeMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	virtual void BindCallbacksToDependencies() override;
	virtual void BroadcastInitialValues() override;
	// Delegate
	UPROPERTY(BlueprintAssignable, Category= "GAS|Attributes")
	FAttributeInfoSignature AttributeInfoDelegate;

protected:
	// Remember, this is a TArray.
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAttributeInfo> AttributeInfo;
};
