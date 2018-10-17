// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorSwingReliance.generated.h"

UCLASS()
class DARKHORSEUNREAL_API ADoorSwingReliance : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleDefaultsOnly)					//Creating a pointer of type static mesh
	class UStaticMeshComponent* DoorFrame;

	UPROPERTY(VisibleDefaultsOnly)					//Creating a pointer of type static mesh door 1
	class UStaticMeshComponent* Door;

	UPROPERTY(VisibleDefaultsOnly)					//Creating a pointer of type static mesh for door2
	class UStaticMeshComponent* Door2;

	UPROPERTY(VisibleDefaultsOnly)					//Creating a pointer of type box component
	class UBoxComponent* PressurePlate;

	bool Opening;									//Set To true if the current state of the door is opening
	bool Closing;									//Set To true if the current state of the door is closing
	bool isClosed;									//Is set to false if the door is open

	float MaxDegree;								//Sets the maximum degree to which the door can rotate
	float AddRotation;								//Stores the amount of rotation to be done each frame
	float Door1CurrentRotation;						//Stores the 1st door rotation

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Sets default values for this actor's properties
	ADoorSwingReliance();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Function that gets called when the door is to be opened
	UFUNCTION()
	void OpenDoor(float dt);

	//Function that gets called when the door is to be closed
	UFUNCTION()
	void CloseDoor(float dt);

	//Function that gets called to toggle opening/closing of door 
	UFUNCTION()
	void ToggleDoor();
	
	
};
