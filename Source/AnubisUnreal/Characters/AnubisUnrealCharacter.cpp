// Copyright Epic Games, Inc. All Rights Reserved.

#include "AnubisUnrealCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "AnubisUnreal/Macros.h"
#include "AnubisUnreal/Abilities/PlayerAttributeSet.h"
#include "AnubisUnreal/UI/AnubisHUD.h"
#include "Kismet/GameplayStatics.h"


DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AAnubisUnrealCharacter

AAnubisUnrealCharacter::AAnubisUnrealCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	// Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create Ability System Component
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

	// Create PlayerAttribute Set
	PlayerAttributeSet = CreateDefaultSubobject<UPlayerAttributeSet>(TEXT("PlayerAttributeSet"));


	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AAnubisUnrealCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AAnubisUnrealCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AAnubisUnrealCharacter::MyJump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAnubisUnrealCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AAnubisUnrealCharacter::Look);

		// Attacking
		//** Light Attack
		EnhancedInputComponent->BindAction(LightAttackAction, ETriggerEvent::Triggered, this,
		                                   &AAnubisUnrealCharacter::LightAttack);
		//** Kick
		EnhancedInputComponent->BindAction(KickAction, ETriggerEvent::Triggered, this, &AAnubisUnrealCharacter::Kick);

		// Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AAnubisUnrealCharacter::Interact);
		
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error,
		       TEXT(
			       "'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."
		       ), *GetNameSafe(this));
	}
}


inline void AAnubisUnrealCharacter::BeginPlay()
{
	Super::BeginPlay();
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	GiveDefaultAbilities();
	InitDefaultAttributes();
	InitHUD();
}

void AAnubisUnrealCharacter::GetHit()
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->CancelAllAbilities();
	}
}

void AAnubisUnrealCharacter::PerformDeath()
{
	//maybe Ability called Death? that has gameplay cue with sound etc?
	if (DeathSequence)
	{
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationSingleNode);
		GetMesh()->PlayAnimation(DeathSequence, false);
		if (DeathClip != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(),DeathClip,GetActorLocation());
		}
		FTimerHandle MontageEndHandle;
		GetWorldTimerManager().SetTimer(MontageEndHandle, this, &AAnubisUnrealCharacter::RestartLevel, 7, false);
	}
	else
	{
		// Fallback if animation missing
		RestartLevel();
	}
}

void AAnubisUnrealCharacter::RestartLevel()
{
	UWorld* World = GetWorld();
	if (!World) return;

	FString MapPackageName = World->GetCurrentLevel()->GetOutermost()->GetName(); // e.g., "/Game/Maps/Start_Level"
	UE_LOG(LogTemp, Warning, TEXT("Restarting level (full path): %s"), *MapPackageName);

	UGameplayStatics::OpenLevel(this, FName(*MapPackageName));
}

void AAnubisUnrealCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (PlayerAttributeSet)
	{
		if (PlayerAttributeSet->GetHealth() <= 0 && bIsAlive)
		{
			bIsAlive = false;
			PerformDeath();

		}
	}
}

void AAnubisUnrealCharacter::InitHUD() const
{
	if (const APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (AAnubisHUD* AnubisHUD = Cast<AAnubisHUD>(PlayerController->GetHUD()))
		{
			AnubisHUD->Init();
		}
	}
}



void AAnubisUnrealCharacter::Move(const FInputActionValue& Value)
{
	if (!bIsAlive) return;

	//maybe do not check all these tags
	//create new tag - State.immovable, that will assign all abilities with which you cannot move
	//and check only one tag - or create ability move? maybe
	
	//Do not move if Kicking
	if (AbilitySystemComponent
		&& AbilitySystemComponent->HasMatchingGameplayTag(StateIsKickingTag)
		|| AbilitySystemComponent->HasMatchingGameplayTag(StateIsStaggeredTag)
		) return;

	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AAnubisUnrealCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AAnubisUnrealCharacter::LightAttack()
{
	if (!AbilitySystemComponent || !bIsAlive) return;

	AbilitySystemComponent->TryActivateAbilitiesByTag(FGameplayTagContainer(AbilityLightAttackTag));
}

void AAnubisUnrealCharacter::Kick()
{
	if (!AbilitySystemComponent || GetCharacterMovement()->IsFalling() || !bIsAlive) return;

	AbilitySystemComponent->TryActivateAbilitiesByTag(FGameplayTagContainer(AbilityKickTag));
}

void AAnubisUnrealCharacter::MyJump()
{
	if (!AbilitySystemComponent || GetCharacterMovement()->IsFalling() || !bIsAlive) return;

	AbilitySystemComponent->TryActivateAbilitiesByTag(FGameplayTagContainer(AbilityMyJumpTag));
	
}

void AAnubisUnrealCharacter::Interact()
{
	if (!bIsAlive) return;
	
	//TODO ABILITY INTERACT
	if (Interactable != nullptr)
	{
		Interactable->Interact();
	}
}


void AAnubisUnrealCharacter::GiveDefaultAbilities()
{
	//Critical assertion - crash immediately if the ASC is nullptr
	check(AbilitySystemComponent);

	//ASC give all abilities set in array of default abilities (set in blueprint editor)
	for (TSubclassOf<UGameplayAbility> AbilityClass : DefaultAbilities)
	{
		const FGameplayAbilitySpec AbilitySpec(AbilityClass, 1);
		AbilitySystemComponent->GiveAbility(AbilitySpec);
	}
}

void AAnubisUnrealCharacter::InitDefaultAttributes()
{
	//check if components are valid
	// DefaultAttributeEffect should be set via blueprint or constructor
	if (!AbilitySystemComponent || !DefaultAttributeEffect) return;

	//Make context that stores metadata about how/why is effect applied (source actor, hit result, etc.)
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();

	//adding this actor as source of the effect
	EffectContext.AddSourceObject(this);

	//Create instance of DefaultAttributeEffect
	const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(
		DefaultAttributeEffect, 1.f, EffectContext);

	//If the instance (SpecHandle) is valid - set the default attributes (apply default effect)
	if (SpecHandle.IsValid())
	{
		AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		PlayerAttributeSet->bAttributesInitialized = true;
	}

	
}
