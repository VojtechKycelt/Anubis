// Made by sir Wok for AnubisUnreal project

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacterBase.h"
#include "Perception/PawnSensingComponent.h"
#include "MummyCharacter.generated.h"

class UPawnSensingComponent;

UCLASS()
class ANUBISUNREAL_API AMummyCharacter : public AEnemyCharacterBase
{
	GENERATED_BODY()

public:
	AMummyCharacter();
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnSeePawn(APawn* Pawn);
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "AI")
	TObjectPtr<UPawnSensingComponent> PawnSensingComponent;
};

