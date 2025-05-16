// Made by sir Wok for AnubisUnreal project


#include "MummyCharacter.h"
#include "AIController.h"
#include "AnubisUnreal/Macros.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"


AMummyCharacter::AMummyCharacter()
{
	
}

void AMummyCharacter::GetHit()
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->CancelAllAbilities();
	}
}

void AMummyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMummyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PlayerCharacter || !AIController) return;

	FVector PlayerLocation = PlayerCharacter->GetActorLocation();
	float DistanceFromPlayer = FVector::Dist(PlayerLocation, GetActorLocation());
	FGameplayTagContainer OwnedTags = AbilitySystemComponent->GetOwnedGameplayTags();
	bIsStaggered = OwnedTags.HasTag(FGameplayTag::RequestGameplayTag("State.IsStaggered"));
	
	if (DistanceFromPlayer < fChaseRadius)
	{
		TargetPosition = PlayerLocation;
	}
	if (!bIsStaggered)
	{
		AIController->MoveToLocation(TargetPosition);
	} else
	{
		AIController->StopMovement();
	}
	if (DistanceFromPlayer < fAttackRadius)
	{
		LightAttack();
	}

	//PRINT_SCREEN("%f", PawnSensingComponent->SightRadius);
	SPHERE_TICK(GetActorLocation(), fChaseRadius);
	SPHERE_TICK(GetActorLocation(), fAttackRadius);
}

void AMummyCharacter::ChasePlayerBehaviour(const FVector& PlayerLocation)
{
	//AIController->bAllowStrafe = true;
	AIController->MoveToLocation(PlayerLocation);
}

void AMummyCharacter::LightAttack()
{
	if (!AbilitySystemComponent) return;
	FGameplayTagContainer OwnedTags = AbilitySystemComponent->GetOwnedGameplayTags();
	if (OwnedTags.HasTag(FGameplayTag::RequestGameplayTag("State.isLightAttacking")) ||
		OwnedTags.HasTag(FGameplayTag::RequestGameplayTag("State.IsStaggered")))
	{
		return;
	};

	FGameplayTag LightAttackTag = FGameplayTag::RequestGameplayTag("Abilities.LightAttack");
	AbilitySystemComponent->TryActivateAbilitiesByTag(FGameplayTagContainer(LightAttackTag));
}
