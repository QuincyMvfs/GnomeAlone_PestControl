// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GnomeAloneGameMode.generated.h"

UCLASS(minimalapi)
class AGnomeAloneGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGnomeAloneGameMode();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MaxDestruction = 500.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int TotalGnomeLives = 10;
};



