// Fill out your copyright notice in the Description page of Project Settings.


#include "GnomeAloneGameState.h"

#include "GnomeAlone/GnomeAloneGameMode.h"
#include "Net/UnrealNetwork.h"

void AGnomeAloneGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGnomeAloneGameState, TotalDestruction);
	DOREPLIFETIME(AGnomeAloneGameState, MaxDestruction);
}

void AGnomeAloneGameState::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		if (const AGnomeAloneGameMode *GM = Cast<AGnomeAloneGameMode>(GetWorld()->GetAuthGameMode()))
		{
			MaxDestruction = GM->MaxDestruction;
			UE_LOG(LogTemp, Warning, TEXT("GameState | Max Destruction: %f"), MaxDestruction);
		}
	}
}

void AGnomeAloneGameState::ObjectDestroyed(AActor* Destroyer, AActor* Destroyed, float Amount)
{
	if (Destroyed)
	{
		TotalDestruction += Amount;
		TotalDestruction = FMath::Clamp(TotalDestruction, 0, MaxDestruction);
		UE_LOG(LogTemp, Warning, TEXT("DESTROYED %s | %f | NEW TOTAL DESTRUCTION: %f"),
			*Destroyed->GetName(), Amount, TotalDestruction);

		OnObjectDestroyedEvent.Broadcast(Destroyed, Amount, TotalDestruction);
	}
}
