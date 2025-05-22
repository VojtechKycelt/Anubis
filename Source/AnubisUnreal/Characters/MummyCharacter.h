// Made by sir Wok for AnubisUnreal project

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacterBase.h"
#include "MummyCharacter.generated.h"

UCLASS()
class ANUBISUNREAL_API AMummyCharacter : public AEnemyCharacterBase
{
	GENERATED_BODY()

	
public:
	AMummyCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void LightAttack();
	bool CanSeePlayer();
	
	bool bPlayerInSightRange = false;
	bool bPlayerInAttackRange = false;
	bool bIsStaggered = false;
	
	FVector TargetPosition;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="AI")
	float fChaseRadius = 1000;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="AI")
	float fAttackRadius = 300;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="AI")
	bool bShowDebug = false;
	
	UFUNCTION(BlueprintCallable)
	void GetHit();
};

