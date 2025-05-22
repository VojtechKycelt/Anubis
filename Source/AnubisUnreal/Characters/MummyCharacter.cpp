// Made by sir Wok for AnubisUnreal project


#include "MummyCharacter.h"
#include "AIController.h"
#include "AnubisUnrealCharacter.h"
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
	bIsStaggered = OwnedTags.HasTag(StateIsStaggeredTag);

	//Update players last seen position if see player in distance
	if (CanSeePlayer() && DistanceFromPlayer < fChaseRadius)
	{
		TargetPosition = PlayerLocation;
	}

	//Move to last seen position if not staggered
	if (!bIsStaggered)
	{
		AIController->MoveToLocation(TargetPosition);
	}
	else
	{
		AIController->StopMovement();
	}

	
	if (DistanceFromPlayer < fAttackRadius)
	{
		//Can smell the player if he is really close
		TargetPosition = PlayerLocation;
		LightAttack();
	}

	if (bShowDebug)
	{
		SPHERE_TICK_COLOR(GetActorLocation(), fChaseRadius, FColor::Green);
		SPHERE_TICK_COLOR(GetActorLocation(), fAttackRadius, FColor::Red);
	}
	
}

void AMummyCharacter::LightAttack()
{
	if (!AbilitySystemComponent) return;
	FGameplayTagContainer OwnedTags = AbilitySystemComponent->GetOwnedGameplayTags();
	if (OwnedTags.HasTag(StateIsLightAttackingTag) ||
		OwnedTags.HasTag(StateIsStaggeredTag))
	{
		return;
	};

	AbilitySystemComponent->TryActivateAbilitiesByTag(FGameplayTagContainer(AbilitiesLightAttackTag));
}

bool AMummyCharacter::CanSeePlayer()
{
	if (!PlayerCharacter) return false;

	//Is player visible from mummy
	FVector Start = GetActorLocation();
	FVector End = PlayerCharacter->GetActorLocation();

	FHitResult HitResult;
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult, Start, End, ECC_Visibility, CollisionQueryParams);
	bool bHitPlayer = bHit && HitResult.GetActor() == PlayerCharacter;
	

	//Is player in FOV of mummy
	FVector Forward = GetActorForwardVector();
	FVector ToPlayer = PlayerCharacter->GetActorLocation() - GetActorLocation();
	ToPlayer.Normalize();
	float Dot = FVector::DotProduct(Forward, ToPlayer);
	float AngleDegrees = FMath::RadiansToDegrees(acosf(Dot));

	bool bIsPlayerInFOV = AngleDegrees < 45.f;

	if (bShowDebug)
	{
		if (bHitPlayer)
		{
			LINE_TICK_COLOR(Start,End,FColor::Red);

		} else
		{
			LINE_TICK_COLOR(Start,End,FColor::Green);

		}
	}
	
	return bHitPlayer && bIsPlayerInFOV;
	
}
