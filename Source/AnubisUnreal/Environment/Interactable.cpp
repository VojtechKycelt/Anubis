// Made by sir Wok for AnubisUnreal project


#include "Interactable.h"
#include "Macros.h"
#include "Characters/AnubisUnrealCharacter.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UI/AnubisHUD.h"


AInteractable::AInteractable()
{
	 // PrimaryActorTick.bCanEverTick = false;

	InteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionSphere"));
	RootComponent = InteractionSphere;

	InteractionSphere->InitSphereRadius(100.0f);
	InteractionSphere->SetHiddenInGame(true);
	InteractionSphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	InteractionSphere->OnComponentBeginOverlap.AddDynamic(this, &AInteractable::OnOverlapBegin);
	InteractionSphere->OnComponentEndOverlap.AddDynamic(this, &AInteractable::OnOverlapEnd);
	
}

void AInteractable::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		AAnubisUnrealCharacter* PlayerCharacter = Cast<AAnubisUnrealCharacter>( UGameplayStatics::GetPlayerCharacter(GetWorld(),0));

		if (PlayerCharacter && OtherActor == PlayerCharacter)
		{
			PlayerCharacter->SetInteractable(this);

			if (const APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0)))
			{
				if (AAnubisHUD* AnubisHUD = Cast<AAnubisHUD>(PlayerController->GetHUD()))
				{
					AnubisHUD->ShowHint(HintTextHud);
				}
			}
		}
	}
}

void AInteractable::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this)
	{
		AAnubisUnrealCharacter* PlayerCharacter = Cast<AAnubisUnrealCharacter>( UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
		if (PlayerCharacter && OtherActor == PlayerCharacter)
		{
			PlayerCharacter->SetInteractable(nullptr);

			if (const APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0)))
			{
				if (AAnubisHUD* AnubisHUD = Cast<AAnubisHUD>(PlayerController->GetHUD()))
				{
					AnubisHUD->HideHint();
				}
			}
		}
	}
}

void AInteractable::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("Interactable::Interact not implemented in child class"));
}

void AInteractable::PlayInteractSound()
{
	if (DefaultAudioClip)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(),DefaultAudioClip,GetActorLocation());
	}
}

