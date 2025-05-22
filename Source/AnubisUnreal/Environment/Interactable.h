// Made by sir Wok for AnubisUnreal project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.generated.h"

UCLASS()
class ANUBISUNREAL_API AInteractable : public AActor
{
	GENERATED_BODY()

protected:
	//Set in viewport
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	class USphereComponent* InteractionSphere;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
					  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Audio")
	class USoundBase* DefaultAudioClip;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="UI")
	FText HintTextHud;
	
public:
	AInteractable();

	virtual void Interact();

	virtual void PlayInteractSound();
	
};
