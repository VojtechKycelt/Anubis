// Made by sir Wok for AnubisUnreal project

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AttributeSetBase.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

#define NUMERIC_VALUE(AttributeSetName, PropertyName) \
AttributeSetName->Get##PropertyName##Attribute().GetNumericValue(AttributeSetName)

/**
 * 
 */
UCLASS()
class ANUBISUNREAL_API UAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()
public:

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	
	UPROPERTY(BlueprintReadOnly, Category = "Abilities | Gameplay Attribute")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, Health);

	UPROPERTY(BlueprintReadOnly, Category = "Abilities | Gameplay Attribute")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, MaxHealth);

	bool bAttributesInitialized = false;
};
