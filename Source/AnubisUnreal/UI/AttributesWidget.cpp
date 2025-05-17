// Made by sir Wok for AnubisUnreal project


#include "AttributesWidget.h"

#include "Macros.h"
#include "Abilities/PlayerAttributeSet.h"
#include "Characters/AnubisUnrealCharacter.h"

void UAttributesWidget::BindToAttributes()
{
	const AAnubisUnrealCharacter* AnubisUnrealCharacter = Cast<AAnubisUnrealCharacter>(GetOwningPlayer()->GetPawn());
	if (!AnubisUnrealCharacter) return;

	UAbilitySystemComponent* ASC = AnubisUnrealCharacter->AbilitySystemComponent;
	const UPlayerAttributeSet* PlayerAttributeSet = AnubisUnrealCharacter->PlayerAttributeSet;

	//Initial Attributes
	HealthPercent = NUMERIC_VALUE(PlayerAttributeSet, Health) / NUMERIC_VALUE(PlayerAttributeSet, MaxHealth);
	StaminaPercent = NUMERIC_VALUE(PlayerAttributeSet, Stamina) / NUMERIC_VALUE(PlayerAttributeSet, MaxStamina);

	// Attribute changes binding
	ASC->GetGameplayAttributeValueChangeDelegate(PlayerAttributeSet->GetHealthAttribute()).AddLambda(
		[this,PlayerAttributeSet](const FOnAttributeChangeData& Data)-> void
		{
			HealthPercent = Data.NewValue / NUMERIC_VALUE(PlayerAttributeSet, MaxHealth);
		}
	);
	ASC->GetGameplayAttributeValueChangeDelegate(PlayerAttributeSet->GetStaminaAttribute()).AddLambda(
		[this,PlayerAttributeSet](const FOnAttributeChangeData& Data)-> void
		{
			StaminaPercent = Data.NewValue / NUMERIC_VALUE(PlayerAttributeSet, MaxStamina);
		}
	);
}
