// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorSwing.generated.h"

UCLASS()
class DARKHORSEUNREAL_API ADoorSwing : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly)					//Creating a pointer of type static mesh
	class UStaticMeshComponent* DoorFrame;

	UPROPERTY(VisibleDefaultsOnly)					//Creating a pointer of type static mesh
	class UStaticMeshComponent* Door;

	UPROPERTY(VisibleDefaultsOnly)					//Creating a pointer of type box component
	class UBoxComponent* PressurePlate;

	bool Opening;									//Defines the status of the door
	bool Closing;
	bool isClosed;									//Is set to false if the door is open

	float MaxDegree;								//The Max Degree to which the door can open
	float AddRotation;								//Stores the amount of rotation to be done every frame
	float DoorCurrentRotation;						//Stores the current rotation of the door
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	ADoorSwing();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Variable to define left/right swing of door true if left swing
	UPROPERTY(EditDefaultsOnly, Category = "DoorSwing")
	bool LSwing;

	//Function To Open The Door
	UFUNCTION()
	void OpenDoor(float dt);

	//Function to Close the Door
	UFUNCTION()
	void CloseDoor(float dt);

	//Function that recieves input from the character and toggles if door can be opened or not
	UFUNCTION()
	void ToggleDoor();
	
};
