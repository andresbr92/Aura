// AndresD3v

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AttributeInfo.generated.h"
USTRUCT(BlueprintType)
struct FAuraAttributeInfo
{
	GENERATED_BODY()

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag AttributeTag = FGameplayTag();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText AttributeName = FText();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText AttributeDescription = FText();

	UPROPERTY(BlueprintReadOnly)
	float AttributeValue = 0.f;
	
	
};
/**
 * @brief This is a data asset that contains the information for each attribute in the game.
 * @note The attribute information is setted in the editor.
 */
UCLASS()
class AURA_API UAttributeInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	
	/**
	 * @brief Return the attribute info for a given attribute tag
	 * @param AttributeTag The attribute tag to get the info for
	 * @param bLogNotFound Whether to log an error if the attribute tag is not found
	 * @return The attribute info for the given attribute tag
	 */
	FAuraAttributeInfo GetAttributeInfoByGameplayTag(const FGameplayTag& AttributeTag, bool bLogNotFound = false) const;

	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FAuraAttributeInfo> AttributeInformation;
	
};
