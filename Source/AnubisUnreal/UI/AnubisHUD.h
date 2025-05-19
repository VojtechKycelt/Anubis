// Made by sir Wok for AnubisUnreal project

#pragma once

#include "CoreMinimal.h"
//#include "AttributesWidget.h"
#include "GameFramework/HUD.h"
#include "AnubisHUD.generated.h"

class UAttributesWidget;
/**
 * 
 */
UCLASS()
class ANUBISUNREAL_API AAnubisHUD : public AHUD
{
	GENERATED_BODY()

public:
	void Init();
	void PauseMenu();
protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAttributesWidget> AttributesWidgetClass; //reference to class, set in editor in AnubisHUD

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> PauseWidgetClass; //reference to class, set in editor in AnubisHUD
	
private:
	UPROPERTY()
	TObjectPtr<UAttributesWidget> AttributesWidget; //instance of the actual widget
	UPROPERTY()
	TObjectPtr<UUserWidget> PauseWidget; //instance of the Pause Widget
};
