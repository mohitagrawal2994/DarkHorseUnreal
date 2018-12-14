// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "Elevator.generated.h"

UCLASS()
class DARKHORSEUNREAL_API AElevator : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* ElevatorMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* Bar1Mesh;

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* Bar2Mesh;

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* Door1Mesh;

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* Door2Mesh;

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* Button1Mesh;

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* Button2Mesh;

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* Button3Mesh;

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* Button4Mesh;

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* Button5Mesh;

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* Button6Mesh;

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* Button7Mesh;

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* Button8Mesh;

	//Timeline for the doors
	FTimeline DoorTimeline;

	//Stores the current float value of the curve
	float CurveFloatValue;

	//Creating a timer handle so that the door closes after certain seconds
	FTimerHandle DoorTimerHandle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	AElevator();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Variable to hold the curve float
	UPROPERTY(EditDefaultsOnly, Category = "Timeline")
	class UCurveFloat* ElevatorDoorCurve;

	//Variable to hold how much the time the doors stay opened
	UPROPERTY(EditDefaultsOnly, Category = "DelayTimer")
	float DelayValue;

	//Function To Open and Close the lift doors
	void OpenDoors();
	void CloseDoors();

	//Timeline Functions
	UFUNCTION()
	void DoorTimelineRun();

	UFUNCTION()
	void DoorTimelineEnd();

	void SetLiftCall(bool ElevatorUpCallStatus, int ECFloorNo);

};
