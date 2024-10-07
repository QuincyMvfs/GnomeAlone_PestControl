// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GnomeAlone/GnomeAloneCharacter.h"
#include "GnomeCharacter.generated.h"

/**
 * 
 */
UCLASS()
class GNOMEALONE_API AGnomeCharacter : public AGnomeAloneCharacter
{
	GENERATED_BODY()
	
protected:
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SprintAction;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void SetSprinting();

	UFUNCTION(Server, Unreliable)
	void Server_SetSprinting(bool IsSprinting, float NewSprintSpeed);
	void Server_SetSprinting_Implementation(bool IsSprinting, float NewSprintSpeed);

	UFUNCTION(NetMulticast, Unreliable)
	void Multi_SetSprinting(bool IsSprinting, float NewSprintSpeed);
	void Multi_SetSprinting_Implementation(bool IsSprinting, float NewSprintSpeed);
	
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	float M_SneakSpeed = 40.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	float M_WalkSpeed = 80.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	float M_SprintSpeed = 160.0f;
	
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly)
	bool M_IsSprinting = false;
};
