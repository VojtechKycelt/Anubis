// Made by sir Wok for AnubisUnreal project


#include "Potion.h"

#include "Characters/AnubisUnrealCharacter.h"
#include "Kismet/GameplayStatics.h"

APotion::APotion()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APotion::Interact()
{
	PlayInteractSound();
	AAnubisUnrealCharacter* PlayerCharacter = Cast<AAnubisUnrealCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	if (PlayerCharacter)
	{
		ApplyEffectToPlayer(*PlayerCharacter);		
	}
}

void APotion::ApplyEffectToPlayer(AAnubisUnrealCharacter& PlayerCharacter)
{
	PlayerCharacter.ApplyEffectToSelf(GameplayEffectClass);

	Destroy();
}


