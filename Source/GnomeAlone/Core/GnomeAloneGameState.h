// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "GnomeAloneGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnObjectDestroyed, AActor*, Destroyed, float, Amount, float, TotalDestruction);


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

	UPROPERTY(BlueprintAssignable)
	FOnObjectDestroyed OnObjectDestroyedEvent;
	
	UFUNCTION(BlueprintCallable)
	void ObjectDestroyed(AActor* Destroyer, AActor* Destroyed, float Amount);
};
