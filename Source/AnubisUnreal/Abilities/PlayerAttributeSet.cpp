// Made by sir Wok for AnubisUnreal project


#include "PlayerAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "AnubisUnreal/Macros.h"

UPlayerAttributeSet::UPlayerAttributeSet()
{
	//InitHealth(85);
}

void UPlayerAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if (!bAttributesInitialized) return;
	
	if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		SetStamina(FMath::Clamp(GetStamina(), 0,GetMaxStamina()));
	}
}
