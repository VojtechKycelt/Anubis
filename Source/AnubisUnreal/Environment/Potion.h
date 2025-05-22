// Made by sir Wok for AnubisUnreal project

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "Interactable.h"
#include "Potion.generated.h"

class AAnubisUnrealCharacter;

UCLASS()
class ANUBISUNREAL_API APotion : public AInteractable
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Abilities | Gameplay Effect", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayEffect> GameplayEffectClass;
	
public:
	APotion();

	virtual void Interact() override;

protected:
	virtual void ApplyEffectToPlayer(AAnubisUnrealCharacter& PlayerCharacter);

};
