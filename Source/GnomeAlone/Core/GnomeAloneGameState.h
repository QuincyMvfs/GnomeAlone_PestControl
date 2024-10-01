// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "GnomeAloneGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnObjectDestroyed, AActor*, Destroyed, float, Amount, float, TotalDestruction);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnGnomeKilled, AActor*, Killed, AActor*, Killer, int, RemainingLives);


UCLASS()
class GNOMEALONE_API AGnomeAloneGameState : public AGameStateBase
{
	GENERATED_BODY()

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void BeginPlay() override;
public:
	// Game Properties
	UPROPERTY(Replicated, BlueprintReadOnly, VisibleAnywhere)
	float TotalDestruction = 0.0f;

	UPROPERTY(Replicated, BlueprintReadOnly, VisibleAnywhere)
	float MaxDestruction = 10.0f;

	UPROPERTY(Replicated, BlueprintReadOnly, VisibleAnywhere)
	int RemainingGnomeLives = 0;

	UPROPERTY(Replicated, BlueprintReadOnly, VisibleAnywhere)
	int TotalGnomeLives = 10;

	UPROPERTY(BlueprintAssignable)
	FOnObjectDestroyed OnObjectDestroyedEvent;

	UPROPERTY(BlueprintAssignable)
	FOnGnomeKilled OnGnomeKilledEvent;
	
	UFUNCTION(BlueprintCallable)
	void ObjectDestroyed(AActor* Destroyer, AActor* Destroyed, float Amount);

	UFUNCTION(BlueprintCallable)
	void GnomeKilled(AActor* Killed, AActor* Killer);
};
