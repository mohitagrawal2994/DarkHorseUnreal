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

	bool Opening;
	bool Closing;
	bool isClosed;									//Is set to false if the door is open

	float MaxDegree;
	float AddRotation;
	float DoorCurrentRotation;
	
public:	
	// Sets default values for this actor's properties
	ADoorSwing();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Function that gets called when the door is to be opened
	UFUNCTION()
	void OpenDoor(float dt);

	//Function that gets called when door is to be closed
	UFUNCTION()
	void CloseDoor(float dt);

	//Function that gets called to toggle opening/closing of door 
	UFUNCTION()
	void ToggleDoor();

	//Set to true when door hinge is on left side
	UPROPERTY(EditDefaultsOnly)
	bool LSwing;

};
