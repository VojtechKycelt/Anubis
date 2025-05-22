// Made by sir Wok for AnubisUnreal project

#include "LevelEnd.h"
#include "Macros.h"
#include "Kismet/GameplayStatics.h"

ALevelEnd::ALevelEnd()
{
	
}

void ALevelEnd::Interact()
{
	//TODO Add FadeOut from scene as HUD overlay alpha change and FadeIn on new scene begin play
	PlayInteractSound();
	FTimerHandle MontageEndHandle;
	GetWorldTimerManager().SetTimer(MontageEndHandle, this, &ALevelEnd::ChangeLevel, 2, false);
}

void ALevelEnd::ChangeLevel() const
{
	FName LevelName;
	
	if (NextLevel.IsValid())
	{
		LevelName = FName(*NextLevel.GetAssetName());
	}
	else if (NextLevel.ToSoftObjectPath().IsValid())
	{
		LevelName = FName(*NextLevel.ToSoftObjectPath().GetAssetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("NO NEXT LEVEL FOUND"));
		return;
	}
	UGameplayStatics::OpenLevel(this, LevelName);
}

