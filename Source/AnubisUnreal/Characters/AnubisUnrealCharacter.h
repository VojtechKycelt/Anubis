// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "AbilitySystemComponent.h"
#include "Environment/Interactable.h"
#include "AnubisUnrealCharacter.generated.h"

class UPlayerAttributeSet;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UAbilitySystemComponent;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AAnubisUnrealCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Input Actions */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LightAttackAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* KickAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	//Sole purpose of calling CancelAllAbilities() when getting hit as it is not marked as (BlueprintCallable)
	//Could be refactored as making my own AbilitySystemComponent child class that overrides it
	UFUNCTION(BlueprintCallable)
	void GetHit();

	/** Internal States **/
	UPROPERTY(BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = "true"))
	bool bIsAlive = true;

	UPROPERTY()
	TObjectPtr<AInteractable> Interactable = nullptr;

public:
	AAnubisUnrealCharacter();

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	/** Ability System Component **/
	//This ASC is owned by same actor as avatar, if we want to keep asc while changing avatars or respawning we
	// need to declare ASC in playerState and include only pointer here so it doesn't get lost while changing avatars
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	/** Set of Attributes - Health, MaxHealth, Stamina, MaxStamina, Strength,.. **/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<UPlayerAttributeSet> PlayerAttributeSet;

	/** Set of default abilities assigned in editor, given to player in BeginPlay function  **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

	/** Gameplay Effect assigned in editor, sets the default values to our attributes at BeginPlay function **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	TSubclassOf<UGameplayEffect> DefaultAttributeEffect;

	bool IsAlive() const { return bIsAlive; }

	AInteractable* GetInteractable() { return Interactable; }
	void SetInteractable(AInteractable* NewInteractable) { Interactable = NewInteractable; }

	void ApplyEffectToSelf(const TSubclassOf<UGameplayEffect>& GameplayEffect);
	
protected:
	/** Functions binded to InputActions in SetupPlayerInputComponent **/
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void LightAttack();
	void Kick();
	void MyJump();
	void Interact();

	/** Called when health == 0 **/
	void PerformDeath();
	void RestartLevel();

	/** Initial functions called on BeginPlay **/
	void GiveDefaultAbilities();
	void InitDefaultAttributes();
	void InitHUD() const;

	virtual void NotifyControllerChanged() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	/** Gameplay Tags **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Abilities")
	FGameplayTag AbilityLightAttackTag;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Abilities")
	FGameplayTag AbilityKickTag;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Abilities")
	FGameplayTag AbilityMyJumpTag;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Abilities")
	FGameplayTag StateIsKickingTag;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Abilities")
	FGameplayTag StateIsStaggeredTag;

	/** Animation and Sound played on dying **/
	//TODO Maybe make death as ability (animation) and with gameplay cue (sound) ?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimSequence* DeathSequence;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* DeathClip;
};
