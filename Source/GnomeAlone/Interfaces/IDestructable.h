// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IDestructable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIDestructable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GNOMEALONE_API IIDestructable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Destructable)
	void Destroy(AActor* Destroyer, AActor* Destroyed);

	virtual void Destroy_Implementation(AActor* Destroyer, AActor* Destroyed);
};
