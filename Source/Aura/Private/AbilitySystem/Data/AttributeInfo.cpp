// AndresD3v


#include "AbilitySystem/Data/AttributeInfo.h"

FAuraAttributeInfo UAttributeInfo::GetAttributeInfoByGameplayTag(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{
	for (const auto AuraAttributeInfo: AttributeInformation)
	{
		if (AttributeTag == AuraAttributeInfo.AttributeTag)
		{
			return AuraAttributeInfo;
		}
	}
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find info for AttributeTag [%s] on AttributeInfo [%s]"), *AttributeTag.ToString(), *GetNameSafe(this) )
	}
	return FAuraAttributeInfo();
}
