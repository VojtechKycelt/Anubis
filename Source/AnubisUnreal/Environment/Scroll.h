// Made by sir Wok for AnubisUnreal project

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Scroll.generated.h"

UCLASS()
class ANUBISUNREAL_API AScroll : public AInteractable
{
	GENERATED_BODY()

public:
	AScroll();

	virtual void Interact() override;
};
