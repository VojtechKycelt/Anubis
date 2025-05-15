// Made by sir Wok for AnubisUnreal project


#include "AttributeSetBase.h"
#include "GameplayEffectExtension.h"
#include "AnubisUnreal/Macros.h"

void UAttributeSetBase::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if (!bAttributesInitialized) return;
	
	// need to include "GameplayEffectExtension.h"
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0, GetMaxHealth()));
	}
}
