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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	AElevator();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetLift();
};
