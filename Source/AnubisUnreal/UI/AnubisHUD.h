// Made by sir Wok for AnubisUnreal project

#pragma once

#include "CoreMinimal.h"
//#include "AttributesWidget.h"
#include "HintWidget.h"
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
	
	UFUNCTION(BlueprintCallable)
	void ShowHint(const FText& Text);

	UFUNCTION(BlueprintCallable)
	void HideHint();
	
protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAttributesWidget> AttributesWidgetClass; //reference to class, set in editor in AnubisHUD

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> PauseWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UHintWidget> HintWidgetClass;
	
private:
	UPROPERTY()
	TObjectPtr<UAttributesWidget> AttributesWidget; //instance of the actual widget
	
	UPROPERTY()
	TObjectPtr<UUserWidget> PauseWidget; //instance of the Pause Widget
	
	UPROPERTY()
	TObjectPtr<UHintWidget> HintWidget; //instance of the Hint Widget
	
};
