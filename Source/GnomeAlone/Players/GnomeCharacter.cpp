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
	DOREPLIFETIME(AGnomeCharacter, M_IsSneaking);
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

		// Sneaking
		EnhancedInputComponent->BindAction(SneakAction, ETriggerEvent::Started, this, &AGnomeCharacter::SetSneaking);
		EnhancedInputComponent->BindAction(SneakAction, ETriggerEvent::Completed, this, &AGnomeCharacter::SetSneaking);

		// Interacting
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AGnomeCharacter::Interact);

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

void AGnomeCharacter::SetSneaking()
{
	if (M_IsSprinting) return;
	
	M_IsSneaking = !M_IsSneaking;

	float NewSneakSpeed = 0.0f;
	if (M_IsSneaking) { NewSneakSpeed = M_SneakSpeed; }
	else { NewSneakSpeed = M_WalkSpeed; }

	Server_SetSneaking(M_IsSneaking, NewSneakSpeed);
}

void AGnomeCharacter::Server_SetSneaking_Implementation(bool IsSneaking, float NewSpeed)
{
	Multi_SetSneaking(IsSneaking, NewSpeed);
}

void AGnomeCharacter::Multi_SetSneaking_Implementation(bool IsSneaking, float NewSpeed)
{
	if (IsSneaking) { M_CharacterMovementComponent->MaxWalkSpeed = M_SneakSpeed; }
	else { M_CharacterMovementComponent->MaxWalkSpeed = M_WalkSpeed; }
}

void AGnomeCharacter::Interact()
{
	const FVector StartLocation = GetMesh()->GetComponentLocation();
	Server_Interact(StartLocation, this);
}

void AGnomeCharacter::Server_Interact_Implementation(FVector StartPosition, AActor* InteractingActor)
{
	UWorld* World = GetWorld();
	FVector Start = StartPosition;
	FVector End = Start;
	float Radius = 100.0f;
	FHitResult OutHit;
	
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(InteractingActor);

	if (bool bHit = World->SweepSingleByChannel(OutHit, Start, End, FQuat::Identity, ECC_Visibility,
		FCollisionShape::MakeSphere(Radius), CollisionParams))
	{
		DrawDebugSphere(World, OutHit.ImpactPoint, Radius, 32, FColor::Red, false, 1.0f);
		DrawDebugLine(World, Start, End, FColor::Red, false, 1.0f);
	}
	else
	{
		DrawDebugLine(World, Start, End, FColor::Green, false, 1.0f);
	}

	Multi_Interact(StartPosition, InteractingActor);
}

void AGnomeCharacter::Multi_Interact_Implementation(FVector StartPosition, AActor* InteractingActor)
{
	DrawDebugSphere(GetWorld(), StartPosition, 50.0, 32, FColor::Red, false, 1.0f);
}