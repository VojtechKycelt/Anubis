// Made by sir Wok for AnubisUnreal project

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "LevelEnd.generated.h"

UCLASS()
class ANUBISUNREAL_API ALevelEnd : public AInteractable
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	TSoftObjectPtr<UWorld> NextLevel;

	void ChangeLevel() const;

public:
	ALevelEnd();

	virtual void Interact() override;
};
