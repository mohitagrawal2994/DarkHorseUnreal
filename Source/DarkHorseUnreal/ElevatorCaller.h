// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ElevatorCaller.generated.h"

UCLASS()
class DARKHORSEUNREAL_API AElevatorCaller : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* ECaller;

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

	UPROPERTY(EditAnywhere, Category = "FloorNo")
	int FloorNo;

	UPROPERTY(EditAnywhere, Category = "Elevator")
	class AElevator* CurrentElevator;
	
};
