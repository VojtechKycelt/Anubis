// Made by sir Wok for AnubisUnreal project


#include "MummyCharacter.h"
#include "AIController.h"
#include "AnubisUnreal/Macros.h"
#include "Kismet/GameplayStatics.h"


AMummyCharacter::AMummyCharacter()
{
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
}

void AMummyCharacter::OnSeePawn(APawn* Pawn)
{
	//PRINT_SCREEN("SEE PAWN, %s", *GetNameSafe(Pawn));
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AAIController* AIController = Cast<AAIController>(GetController());
	if (PlayerCharacter && AIController)
	{
		AIController->MoveToActor(Pawn);
	}
}


void AMummyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (PawnSensingComponent)
	{
		PawnSensingComponent->OnSeePawn.AddDynamic(this,&AMummyCharacter::OnSeePawn);
	}
}

void AMummyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//PRINT_SCREEN("%f", PawnSensingComponent->SightRadius);
	SPHERE_TICK(GetActorLocation(), PawnSensingComponent->SightRadius);
}


