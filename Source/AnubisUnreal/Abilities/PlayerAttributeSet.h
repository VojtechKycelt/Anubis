// Made by sir Wok for AnubisUnreal project

#pragma once

#include "CoreMinimal.h"
#include "AttributeSetBase.h"
#include "PlayerAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class ANUBISUNREAL_API UPlayerAttributeSet : public UAttributeSetBase
{
	GENERATED_BODY()

public:
	UPlayerAttributeSet();
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(BlueprintReadOnly, Category = "Abilities | Gameplay Attribute")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Stamina);
	
	UPROPERTY(BlueprintReadOnly, Category = "Abilities | Gameplay Attribute")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, MaxStamina);

};
