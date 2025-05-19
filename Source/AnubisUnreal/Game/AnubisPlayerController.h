// Made by sir Wok for AnubisUnreal project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AnubisPlayerController.generated.h"

UCLASS()
class ANUBISUNREAL_API AAnubisPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void SetupInputComponent() override;

public:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* PauseAction;

	void PauseGame();
};
