// Copyright Epic Games, Inc. All Rights Reserved.

#include "AnubisUnrealGameMode.h"
#include "Characters/AnubisUnrealCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAnubisUnrealGameMode::AAnubisUnrealGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
