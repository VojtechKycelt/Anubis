// Made by sir Wok for AnubisUnreal project

#pragma once

#include "CoreMinimal.h"
#include "AttributeSetBase.h"
#include "EnemyAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class ANUBISUNREAL_API UEnemyAttributeSet : public UAttributeSetBase
{
	GENERATED_BODY()

public:
	UEnemyAttributeSet();
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

};
