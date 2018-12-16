// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class DARKHORSEUNREAL_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	//Creating a variable to get the default capsule component
	UPROPERTY(VisibleAnywhere, Category = "Capsule")
	class UCapsuleComponent* CollisionCapsule;

	//Creating a variable to hold the current overlapped door actor
	class ADoorSwing* CurrentDoor;

	//Creating a variable to hold the current overlapped door actor
	class ADoorSwingReliance* RelDoor;

	//Stores The Raytrace Hit Objects and its related data
	FHitResult HitResult;

	//Creating a variable to hold the elevator caller actor
	class AElevator* Elevator;

	//Creating a variable to hold the elevator caller actor
	class AElevatorCaller* ElevatorCaller;

	//Stores the Floor Number at which the lift is being called
	int FloorNumber;

	//Set to true if the elevator caller button was hit
	bool EC;

	//Set to true if Player wishes to travel up in elevator
	bool ElevatorUpCallStatus;

	//Stores the walk speed as set by player in Blueprint
	float OrgWalkSpeed;

	//Handles if the player can climb a ladder
	bool bClimbLadder;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Handles moving forward/backward
	void MoveForward(float Val);

	//Handles stafing movement, left and right
	void MoveRight(float Val);

	//Handles the input for door closing/opening
	void Action();

	//Handles input if player is crouching
	void Crouching();
	void StopCrouching();

	//Handles input if player is sprinting
	void Sprinting();
	void StopSprinting();

public:	
	// Sets default values for this character's properties
	AMyCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Defines the sprinting speed
	UPROPERTY(EditDefaultsOnly, Category = "Sprinting")
	float SprintSpeed;

	//Called to check if the ray trace from player hits anything 
	void RayTrace(FVector StartLocation, FVector EndLocation, FVector LookDirection);

	//Functions to set the value of CanClimbLadder
	void CanClimbLadder();
	void CannotClimbLadder();

};
