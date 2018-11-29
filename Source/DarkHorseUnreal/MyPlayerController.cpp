// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"
#include "MyCharacter.h"
#include "Blueprint/UserWidget.h"

AMyPlayerController::AMyPlayerController()
{
	//Setting the crosshair positions
	CrossHairXLocation = 0.5;
	CrossHairYLocation = 0.5;

	//Setting the range of line trace
	LineTraceRange = 300.0f;

}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	MyCharacter = Cast<AMyCharacter>(GetPawn());

}


void AMyPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimAtCrosshair();
}

void AMyPlayerController::AimAtCrosshair()
{
	//Gets The current viewport size
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	//Finds the screen position of the crosshair
	ScreenLocation = FVector2D(ViewportSizeX*CrossHairXLocation, ViewportSizeY*CrossHairYLocation);

	//Converts the 2D Screen Location to 3D
	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection))
	{
		//The player's camera position
		StartLocation = PlayerCameraManager->GetCameraLocation();

		//The End Line of line trace i.e from camera to range
		EndLocation = StartLocation + (LookDirection*LineTraceRange);

		MyCharacter->RayTrace(StartLocation, EndLocation, LookDirection);
	}

}
