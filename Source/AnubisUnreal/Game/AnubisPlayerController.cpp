// Made by sir Wok for AnubisUnreal project


// AnubisPlayerController.cpp

#include "AnubisPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Macros.h"
#include "Kismet/GameplayStatics.h"
#include "UI/AnubisHUD.h"

void AAnubisPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (PauseAction)
		{
			PauseAction->bTriggerWhenPaused = true; // Required!
			EnhancedInput->BindAction(PauseAction, ETriggerEvent::Triggered, this, &AAnubisPlayerController::PauseGame);
		}
	}
}

void AAnubisPlayerController::PauseGame()
{

	if (AAnubisHUD* HUD = Cast<AAnubisHUD>(GetHUD()))
	{
		HUD->PauseMenu();
	}
}