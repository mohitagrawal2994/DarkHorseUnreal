// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ElevatorCaller.generated.h"

UCLASS()
class DARKHORSEUNREAL_API AElevatorCaller : public AActor
{
	GENERATED_BODY()

	//The mesh to hold buttons
	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* ECaller;

	//Lift caller button
	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* Button1;

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* Button2;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sets default values for this actor's properties
	AElevatorCaller();

	//Stores the floor number of the current elevator caller
	UPROPERTY(EditAnywhere, Category = "Elevator")
	int FloorNo;

	//Set to true when the caller is placed at the lowest floor
	UPROPERTY(EditAnywhere, Category = "Elevator")
	bool OnlyUp;

	//Set to true when the caller is placed at the topmost floor
	UPROPERTY(EditAnywhere, Category = "Elevator")
	bool OnlyDown;

	//Stores the elevator which is controlled by the elevator
	UPROPERTY(EditAnywhere, Category = "Elevator")
	class AElevator* CurrentElevator;

	//Returns the caller floor number
	int GetFloorNo();

	//Returns the elevator controlled by the elevator
	class AElevator* GetCurrentElevator();

};
