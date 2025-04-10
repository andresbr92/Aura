// AndresD3v


#include "AbilitySystem/Data/CharacterClassInfo.h"


#include "AbilitySystem/Data/CharacterClassInfo.h"
 
FCharacterClassDefaultInfo UCharacterClassInfo::GetClassDefaultInfo(ECharacterClass CharacterClass)
{
	return CharacterClassInformation.FindChecked(CharacterClass);
}

