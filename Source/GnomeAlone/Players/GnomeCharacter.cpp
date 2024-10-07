// Fill out your copyright notice in the Description page of Project Settings.


#include "GnomeCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"

void AGnomeCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGnomeCharacter, M_IsSprinting);

}

void AGnomeCharacter::BeginPlay()
{
	Super::BeginPlay();

	M_CharacterMovementComponent->MaxWalkSpeed = M_WalkSpeed;
}

void AGnomeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Sprinting
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AGnomeCharacter::SetSprinting);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AGnomeCharacter::SetSprinting);

		// Interacting
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ACharacter::Jump);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGnomeAloneCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AGnomeAloneCharacter::Look);

	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AGnomeCharacter::SetSprinting()
{
	M_IsSprinting = !M_IsSprinting;
	
	float NewSprintSpeed = 0.0f;
	if (M_IsSprinting) { NewSprintSpeed = M_SprintSpeed; }
	else { NewSprintSpeed = M_WalkSpeed; }
	
	Server_SetSprinting(M_IsSprinting, NewSprintSpeed);
}

void AGnomeCharacter::Server_SetSprinting_Implementation(bool IsSprinting, float NewSprintSpeed)
{
	Multi_SetSprinting(IsSprinting, NewSprintSpeed);
}

void AGnomeCharacter::Multi_SetSprinting_Implementation(bool IsSprinting, float NewSprintSpeed)
{
	if (IsSprinting) { M_CharacterMovementComponent->MaxWalkSpeed = M_SprintSpeed; }
	else { M_CharacterMovementComponent->MaxWalkSpeed = M_WalkSpeed; }
}
