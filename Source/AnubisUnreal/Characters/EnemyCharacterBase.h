﻿// Made by sir Wok for AnubisUnreal project

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AIController.h"
#include "AnubisUnreal/Abilities/EnemyAttributeSet.h"
#include "GameFramework/Character.h"
#include "EnemyCharacterBase.generated.h"

UCLASS()
class ANUBISUNREAL_API AEnemyCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacterBase();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<UEnemyAttributeSet> AttributeSet;

	UPROPERTY()
	TObjectPtr<ACharacter> PlayerCharacter;

	UPROPERTY()
	TObjectPtr<AAIController> AIController;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	TSubclassOf<UGameplayEffect> DefaultAttributeEffect;

	UFUNCTION(BlueprintImplementableEvent, Category = "Events")
	void MyDeathEvent();

	bool bIsDead = false;
	
	void GiveDefaultAbilities();
	void InitDefaultAttributes();
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="AI")
	bool bShowDebug = false;
};
