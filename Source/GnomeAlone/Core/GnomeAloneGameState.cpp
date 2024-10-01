// Fill out your copyright notice in the Description page of Project Settings.


#include "GnomeAloneGameState.h"

#include "GnomeAlone/GnomeAloneGameMode.h"
#include "Net/UnrealNetwork.h"

void AGnomeAloneGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGnomeAloneGameState, TotalDestruction);
	DOREPLIFETIME(AGnomeAloneGameState, MaxDestruction);
	DOREPLIFETIME(AGnomeAloneGameState, RemainingGnomeLives);
	DOREPLIFETIME(AGnomeAloneGameState, TotalGnomeLives);
}

void AGnomeAloneGameState::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		if (const AGnomeAloneGameMode *GM = Cast<AGnomeAloneGameMode>(GetWorld()->GetAuthGameMode()))
		{
			MaxDestruction = GM->MaxDestruction;
			TotalGnomeLives = GM->TotalGnomeLives;
			RemainingGnomeLives = TotalGnomeLives;
		}
	}
}

void AGnomeAloneGameState::ObjectDestroyed(AActor* Destroyer, AActor* Destroyed, float Amount)
{
	if (Destroyed)
	{
		TotalDestruction += Amount;
		TotalDestruction = FMath::Clamp(TotalDestruction, 0, MaxDestruction);
		// UE_LOG(LogTemp, Warning, TEXT("DESTROYED %s | %f | NEW TOTAL DESTRUCTION: %f"),
		// 	*Destroyed->GetName(), Amount, TotalDestruction);

		OnObjectDestroyedEvent.Broadcast(Destroyed, Amount, TotalDestruction);
	}
}

void AGnomeAloneGameState::GnomeKilled(AActor* Killed, AActor* Killer)
{
	if (Killed)
	{
		RemainingGnomeLives--;
		RemainingGnomeLives = FMath::Clamp(RemainingGnomeLives, 0, TotalGnomeLives);

		OnGnomeKilledEvent.Broadcast(Killed, Killer, RemainingGnomeLives);
	}
}
