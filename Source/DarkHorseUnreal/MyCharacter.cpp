// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "DoorSwing.h"
#include "DoorSwingReliance.h"
#include "ElevatorCaller.h"
#include "Elevator.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FPPCamera"));		//Assigning the camera
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	//Setting the Collision capsule variable to recieve the ACharacter CapsuleComponent
	CollisionCapsule = GetCapsuleComponent();

	//Setting ElevatorCallUpStatus
	ElevatorUpCallStatus = true;

	//Setting Default value for WalkSpeed
	OrgWalkSpeed = 1.0f;

	//Setting Default Sprint speed
	SprintSpeed = 1.5f;

	//Setting Crouching to true
	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;

	//Setting can climb ladder to false
	bClimbLadder = false;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	OrgWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	//Bind the DoorAction Event
	PlayerInputComponent->BindAction("Action", IE_Pressed, this, &AMyCharacter::Action);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	//Bind Crouch events
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AMyCharacter::Crouching);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AMyCharacter::StopCrouching);

	//Bind Sprint Events
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMyCharacter::Sprinting);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMyCharacter::StopSprinting);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);

	//Binding The Mouse Axis events
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

}

void AMyCharacter::MoveForward(float Val)
{
	if (Val != 0.0f)
	{
		if (bClimbLadder)
		{
			AddMovementInput(GetActorUpVector(), Val);
		}
		else
		{
			AddMovementInput(GetActorForwardVector(), Val);
		}
	}
}

void AMyCharacter::MoveRight(float Val)
{
	if (Val != 0.0f)
	{
		if (!bClimbLadder)
		{
			AddMovementInput(GetActorRightVector(), Val);
		}
	}
}

//Executes When The Action Button is pressed
void AMyCharacter::Action()
{
	if (CurrentDoor)
	{
		CurrentDoor->ToggleDoor();
	}
	if (RelDoor)
	{
		RelDoor->ToggleDoor();
	}
	if (EC)
	{
		if (Elevator)
		{
			Elevator->SetLiftCall(ElevatorUpCallStatus, FloorNumber);
		}
	}
}

void AMyCharacter::Crouching()
{
	Crouch();
}

void AMyCharacter::StopCrouching()
{
	UnCrouch();
}

void AMyCharacter::Sprinting()
{
	GetCharacterMovement()->MaxWalkSpeed *= SprintSpeed;
}

void AMyCharacter::StopSprinting()
{
	GetCharacterMovement()->MaxWalkSpeed = OrgWalkSpeed;
}

void AMyCharacter::RayTrace(FVector StartLocation, FVector EndLocation, FVector LookDirection)
{
	//Line Tracing 
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility))
	{
		//Checks if the line trace hits something
		if (HitResult.bBlockingHit)
		{
			//Checks If the line trace hit the DoorSwing class 
			if (HitResult.GetActor()->GetClass()->IsChildOf(ADoorSwing::StaticClass()))
			{
				CurrentDoor = Cast<ADoorSwing>(HitResult.GetActor());
			}
			//Checks If the line trace hit the DoorSwingReliance class 
			if (HitResult.GetActor()->GetClass()->IsChildOf(ADoorSwingReliance::StaticClass()))
			{
				RelDoor = Cast<ADoorSwingReliance>(HitResult.GetActor());
			}
			//Checks If the line trace hit the ElevatorCaller class 
			if (HitResult.GetActor()->GetClass()->IsChildOf(AElevatorCaller::StaticClass()))
			{
				//Set to true only if we hit the buttons
				EC = false;

				//Checking if we hit the buttons in the elevator caller
				if (HitResult.GetComponent()->GetName() == "Button1" || HitResult.GetComponent()->GetName() == "Button2")
				{
					EC = true;
					ElevatorCaller = Cast<AElevatorCaller>(HitResult.GetActor());

					//Get Details From the lift caller like floor number and current lift
					FloorNumber = ElevatorCaller->GetFloorNo();
					Elevator = ElevatorCaller->GetCurrentElevator();

					//Set Elevator Call status to go up or down
					if (HitResult.GetComponent()->GetName() == "Button1")
					{
						ElevatorUpCallStatus = true;
					}
					else
					{
						ElevatorUpCallStatus = false;
					}
				}
			}
		}

	}
	else
	{
		CurrentDoor = NULL;
		RelDoor = NULL;
		ElevatorCaller = NULL;
		Elevator = NULL;
	}
}

void AMyCharacter::CanClimbLadder()
{
	bClimbLadder = true;
	GetCharacterMovement()->SetMovementMode(MOVE_Flying);
}

void AMyCharacter::CannotClimbLadder()
{
	bClimbLadder = false;
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);
}

