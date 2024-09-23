// Copyright Epic Games, Inc. All Rights Reserved.

#include "GnomeAloneGameMode.h"
#include "GnomeAloneCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGnomeAloneGameMode::AGnomeAloneGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
