// Made by sir Wok for AnubisUnreal project


#include "EnemyAttributeSet.h"
#include "GameplayEffectExtension.h"

UEnemyAttributeSet::UEnemyAttributeSet()
{
	
}

void UEnemyAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if (!bAttributesInitialized) return;
	
}
