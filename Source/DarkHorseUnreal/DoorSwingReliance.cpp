// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorSwingReliance.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"


// Sets default values
ADoorSwingReliance::ADoorSwingReliance()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));		//Assigning a static mesh component
	RootComponent = DoorFrame;
	DoorFrame->SetMobility(EComponentMobility::Static);									//Setting its mobility static

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));					//Assigning a movable mesh component
	Door->SetupAttachment(RootComponent);
	Door->SetWorldTransform(FTransform(FVector(0, -20.32, 0)));

	Door2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door2"));				//Assigning a movable mesh component
	Door2->SetupAttachment(RootComponent);
	Door2->SetWorldTransform(FTransform(FVector(-228.6, -17.32, 0)));
	Door2->SetWorldRotation(FRotator(0, -180, 0));

	PressurePlate = CreateDefaultSubobject<UBoxComponent>(TEXT("PressurePlate"));		//Assigning a static box component
	PressurePlate->SetupAttachment(RootComponent);
	PressurePlate->SetCollisionProfileName("Trigger");									//Setting its collision preset to be trigger
	PressurePlate->SetMobility(EComponentMobility::Static);								//Setting its mobility static
	PressurePlate->InitBoxExtent(FVector(120, 200, 160));								//Setting the box component size
	PressurePlate->SetWorldTransform(FTransform(FVector(-113.5, 0, 160)));				//Setting the box component transform

	Closing = false;
	Opening = false;
	isClosed = true;

	MaxDegree = 0.0f;
	AddRotation = 0.0f;
	Door1CurrentRotation = 0.0f;
}

// Called when the game starts or when spawned
void ADoorSwingReliance::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoorSwingReliance::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Opening)
	{
		OpenDoor(DeltaTime);
	}
	if (Closing)
	{
		CloseDoor(DeltaTime);
	}
}

void ADoorSwingReliance::OpenDoor(float dt)
{
	Door1CurrentRotation = Door->RelativeRotation.Yaw;
	AddRotation = dt * 120;
	MaxDegree = 90.0f;
	if (FMath::IsNearlyEqual(Door1CurrentRotation, MaxDegree, 1.5f))
	{
		Closing = false;
		Opening = false;
	}
	else if (Opening)
	{
		//FRotator NewRotation = FRotator(0.0f, AddRotation, 0.0f);
		Door->AddRelativeRotation(FQuat(FRotator(0.0f, AddRotation, 0.0f)));
		Door2->AddRelativeRotation(FQuat(FRotator(0.0f, -AddRotation, 0.0f)));
	}
}

void ADoorSwingReliance::CloseDoor(float dt)
{
	Door1CurrentRotation = Door->RelativeRotation.Yaw;
	AddRotation = -dt * 120;
	MaxDegree = 0.0f;
	if (FMath::IsNearlyEqual(Door1CurrentRotation, MaxDegree, 1.5f))
	{
		Closing = false;
		Opening = false;
	}
	else if (Closing)
	{
		Door->AddRelativeRotation(FQuat(FRotator(0.0f, AddRotation, 0.0f)));
		Door2->AddRelativeRotation(FQuat(FRotator(0.0f, -AddRotation, 0.0f)));
	}
}

void ADoorSwingReliance::ToggleDoor()
{
	if (isClosed)
	{
		isClosed = false;
		Closing = false;
		Opening = true;
	}
	else
	{
		isClosed = true;
		Opening = false;
		Closing = true;
	}
}

