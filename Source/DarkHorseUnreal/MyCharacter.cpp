// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "DoorSwing.h"
#include "DoorSwingReliance.h"
#include "Engine/World.h"

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

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	CollisionCapsule->OnComponentBeginOverlap.AddDynamic(this, &AMyCharacter::OnOverlapBegin);
	CollisionCapsule->OnComponentEndOverlap.AddDynamic(this, &AMyCharacter::OnOverlapEnd);

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
		AddMovementInput(GetActorForwardVector(), Val);
	}
}

void AMyCharacter::MoveRight(float Val)
{
	if (Val != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), Val);
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
}

//Executes when an actor/component begins to overlaps the capsule component
void AMyCharacter::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor != nullptr) && (OtherComp != nullptr) && (OtherActor != this) && (OtherActor->GetClass()->IsChildOf(ADoorSwing::StaticClass())))
	{
		CurrentDoor = Cast<ADoorSwing>(OtherActor);
	}
	if ((OtherActor != nullptr) && (OtherComp != nullptr) && (OtherActor != this) && (OtherActor->GetClass()->IsChildOf(ADoorSwingReliance::StaticClass())))
	{
		RelDoor = Cast<ADoorSwingReliance>(OtherActor);
	}
}

//Executes when an actor/component exits overlapping the capsule component
void AMyCharacter::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if ((OtherActor != nullptr) && (OtherComp != nullptr) && (OtherActor != this))
	{
		CurrentDoor = NULL;
	}
	if ((OtherActor != nullptr) && (OtherComp != nullptr) && (OtherActor != this))
	{
		RelDoor = NULL;
	}
}

