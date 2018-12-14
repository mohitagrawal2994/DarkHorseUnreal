// Fill out your copyright notice in the Description page of Project Settings.

#include "Elevator.h"
#include "Components/StaticMeshComponent.h"
#include "Curves/CurveFloat.h"
#include "TimerManager.h"

// Sets default values
AElevator::AElevator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ElevatorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ElevatorMesh"));
	RootComponent = ElevatorMesh;
	ElevatorMesh->SetMobility(EComponentMobility::Movable);

	Bar1Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bar1"));
	Bar1Mesh->SetupAttachment(RootComponent);
	Bar1Mesh->SetWorldTransform(FTransform(FVector(101.5, -5, 102)));				//Setting the mesh component transform

	Bar2Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bar2"));
	Bar2Mesh->SetupAttachment(RootComponent);
	Bar2Mesh->SetWorldTransform(FTransform(FVector(-101.5, -5, 102)));				//Setting the mesh component transform
	Bar2Mesh->SetWorldRotation(FRotator(0.0f, 180.0f, 0.0f));

	Door1Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door1"));
	Door1Mesh->SetupAttachment(RootComponent);
	Door1Mesh->SetWorldTransform(FTransform(FVector(0, 117, 12.7)));				//Setting the mesh component transform

	Door2Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door2"));
	Door2Mesh->SetupAttachment(RootComponent);
	Door2Mesh->SetWorldTransform(FTransform(FVector(0, 122.08, 12.7)));				//Setting the mesh component transform
	Door2Mesh->SetWorldRotation(FRotator(0.0f, 180.0f, 0.0f));
																				
	Button1Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button1"));	//Setting up the buttons
	Button1Mesh->SetupAttachment(RootComponent);
	Button1Mesh->SetWorldTransform(FTransform(FVector(82.8, 115.8, 148.)));
	Button1Mesh->SetWorldRotation(FRotator(0.0f, 0.0f, 180.0f));
	Button1Mesh->SetWorldScale3D(FVector(0.8f, 0.8f, 0.8f));

	Button2Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button2"));
	Button2Mesh->SetupAttachment(RootComponent);
	Button2Mesh->SetWorldTransform(FTransform(FVector(75, 115.8, 148)));
	Button2Mesh->SetWorldRotation(FRotator(0.0f, 0.0f, 180.0f));
	Button2Mesh->SetWorldScale3D(FVector(0.8f, 0.8f, 0.8f));

	Button3Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button3"));
	Button3Mesh->SetupAttachment(RootComponent);
	Button3Mesh->SetWorldTransform(FTransform(FVector(82.8, 115.8, 142.5)));
	Button3Mesh->SetWorldRotation(FRotator(0.0f, 0.0f, 180.0f));
	Button3Mesh->SetWorldScale3D(FVector(0.8f, 0.8f, 0.8f));

	Button4Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button4"));
	Button4Mesh->SetupAttachment(RootComponent);
	Button4Mesh->SetWorldTransform(FTransform(FVector(75, 115.8, 142.5)));
	Button4Mesh->SetWorldRotation(FRotator(0.0f, 0.0f, 180.0f));
	Button4Mesh->SetWorldScale3D(FVector(0.8f, 0.8f, 0.8f));

	Button5Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button5"));
	Button5Mesh->SetupAttachment(RootComponent);
	Button5Mesh->SetWorldTransform(FTransform(FVector(82.8, 115.8, 137)));
	Button5Mesh->SetWorldRotation(FRotator(0.0f, 0.0f, 180.0f));
	Button5Mesh->SetWorldScale3D(FVector(0.8f, 0.8f, 0.8f));

	Button6Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button6"));
	Button6Mesh->SetupAttachment(RootComponent);
	Button6Mesh->SetWorldTransform(FTransform(FVector(75, 115.8, 137)));
	Button6Mesh->SetWorldRotation(FRotator(0.0f, 0.0f, 180.0f));
	Button6Mesh->SetWorldScale3D(FVector(0.8f, 0.8f, 0.8f));

	Button7Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button7"));
	Button7Mesh->SetupAttachment(RootComponent);
	Button7Mesh->SetWorldTransform(FTransform(FVector(82.8, 115.8, 131.5)));
	Button7Mesh->SetWorldRotation(FRotator(0.0f, 0.0f, 180.0f));
	Button7Mesh->SetWorldScale3D(FVector(0.8f, 0.8f, 0.8f));

	Button8Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button8"));
	Button8Mesh->SetupAttachment(RootComponent);
	Button8Mesh->SetWorldTransform(FTransform(FVector(75, 115.8, 131.5)));
	Button8Mesh->SetWorldRotation(FRotator(0.0f, 0.0f, 180.0f));
	Button8Mesh->SetWorldScale3D(FVector(0.8f, 0.8f, 0.8f));

	DelayValue = 5.0f;																//Setting a default delay of 5s	
}

// Called when the game starts or when spawned
void AElevator::BeginPlay()
{
	Super::BeginPlay();

	if (ElevatorDoorCurve)															//If the curve is found 
	{
		FOnTimelineFloat TimelineCallback;											 
		FOnTimelineEventStatic TimelineCallbackFinished;

		TimelineCallback.BindUFunction(this, FName("DoorTimelineRun"));				//Performing binding
		TimelineCallbackFinished.BindUFunction(this, FName("DoorTimelineEnd"));

		DoorTimeline.AddInterpFloat(ElevatorDoorCurve, TimelineCallback);
		DoorTimeline.SetTimelineFinishedFunc(TimelineCallbackFinished);
	}
}

// Called every frame
void AElevator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DoorTimeline.TickTimeline(DeltaTime);
}

void AElevator::DoorTimelineRun()
{
	//Get the current value of the curve in time
	CurveFloatValue = ElevatorDoorCurve->GetFloatValue(DoorTimeline.GetPlaybackPosition());

	//Set the translation value of doors
	Door1Mesh->SetRelativeLocation(FVector(CurveFloatValue, Door1Mesh->RelativeLocation.Y, Door1Mesh->RelativeLocation.Z));
	Door2Mesh->SetRelativeLocation(FVector(-CurveFloatValue, Door2Mesh->RelativeLocation.Y, Door2Mesh->RelativeLocation.Z));

}

void AElevator::DoorTimelineEnd()
{
	//Runs a timer handle so that when the door is open closed after s seconds automatically
	if (CurveFloatValue == 53.63f)
	{
		GetWorldTimerManager().SetTimer(DoorTimerHandle, this, &AElevator::CloseDoors, DelayValue, false);
	}
}

void AElevator::OpenDoors()
{
	if (ElevatorDoorCurve)
	{
		//Calls to the play the timeline from start
		DoorTimeline.PlayFromStart();
	}
}

void AElevator::CloseDoors()
{
	GetWorldTimerManager().ClearTimer(DoorTimerHandle);			//Clears the timer handle
	if (ElevatorDoorCurve)
	{
		//Plays the timeline in reverse
		DoorTimeline.Reverse();
	}
}

void AElevator::SetLiftCall(bool ElevatorUpCallStatus, int ECFloorNo)
{
	OpenDoors();
}
