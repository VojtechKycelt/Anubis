// Made by sir Wok for AnubisUnreal project

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h" // Required for UTextBlock
#include "HintWidget.generated.h"

/**
 * 
 */
UCLASS()
class ANUBISUNREAL_API UHintWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetHintText(const FText& InText);

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* HintTextBlock;
};
