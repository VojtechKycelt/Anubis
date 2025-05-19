// Made by sir Wok for AnubisUnreal project


#include "AnubisHUD.h"
#include "AttributesWidget.h"
#include "Kismet/GameplayStatics.h"

void AAnubisHUD::Init()
{
	AttributesWidget = CreateWidget<UAttributesWidget>(GetOwningPlayerController(), AttributesWidgetClass);
	AttributesWidget->BindToAttributes();
	AttributesWidget->AddToViewport();
}

void AAnubisHUD::PauseMenu()
{
	APlayerController* PlayerController = GetOwningPlayerController();

	if (!UGameplayStatics::IsGamePaused(GetWorld()))
	{
		PauseWidget = CreateWidget<UUserWidget>(PlayerController, PauseWidgetClass);
		PauseWidget->AddToViewport();
	
		// Set input mode to UI only
		FInputModeGameAndUI InputMode;
		InputMode.SetWidgetToFocus(PauseWidget->TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	
		PlayerController->SetInputMode(InputMode);
		PlayerController->bShowMouseCursor = true;

		// Pause the game
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	} else
	{
		PauseWidget->RemoveFromParent();
		FInputModeGameOnly GameInputMode;
		PlayerController->SetInputMode(GameInputMode);
		PlayerController->bShowMouseCursor = false;
		UGameplayStatics::SetGamePaused(GetWorld(), false);
	}
	
}

void AAnubisHUD::ShowHint(const FText& Text)
{
	if (!HintWidgetClass) return;

	UHintWidget* Hint = CreateWidget<UHintWidget>(GetOwningPlayerController(), HintWidgetClass);
	if (!Hint) return;

	Hint->SetHintText(Text);  // Set the text
	Hint->AddToViewport();

	HintWidget = Hint; // Store it if you need to remove/hide it later
}

void AAnubisHUD::HideHint()
{
	HintWidget->RemoveFromParent();
}
