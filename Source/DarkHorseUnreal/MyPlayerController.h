// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 *
 */
UCLASS()
class DARKHORSEUNREAL_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

	//Stores The Current Screen Size
	int32 ViewportSizeX, ViewportSizeY;

	//Stores the current screen crosshair position
	FVector2D ScreenLocation;


	FVector CameraWorldLocation;
	FVector LookDirection;
	FVector StartLocation;
	FVector EndLocation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this character's properties
	AMyPlayerController();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//The X Position of the crosshair
	UPROPERTY(EditDefaultsOnly, Category = "Crosshair Position")
	float CrossHairXLocation;

	//The Y Position of the crosshair
	UPROPERTY(EditDefaultsOnly, Category = "Crosshair Position")
	float CrossHairYLocation;

	//The Range of line trace
	UPROPERTY(EditDefaultsOnly, Category = "Crosshair Position")
	float LineTraceRange;

	class AMyCharacter* MyCharacter;

	//Function to deproject the 2D screen position of crosshair to 3D
	void AimAtCrosshair();
};
