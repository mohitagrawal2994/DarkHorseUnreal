// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorSwing.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ADoorSwing::ADoorSwing()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));		//Assigning a static mesh component
	RootComponent = DoorFrame;
	DoorFrame->SetMobility(EComponentMobility::Static);									//Setting its mobility static

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));					//Assigning a movable mesh component
	Door->SetupAttachment(RootComponent);

	PressurePlate = CreateDefaultSubobject<UBoxComponent>(TEXT("PressurePlate"));		//Assigning a static box component
	PressurePlate->SetupAttachment(RootComponent);
	PressurePlate->SetCollisionProfileName("Trigger");									//Setting its collision preset to be trigger
	PressurePlate->SetMobility(EComponentMobility::Static);								//Setting its mobility static
	PressurePlate->InitBoxExtent(FVector(60, 200, 160));								//Setting the box component size
	PressurePlate->SetWorldTransform(FTransform(FVector(53.35, 0, 160)));				//Setting the box component transform

	Closing = false;
	Opening = false;
	isClosed = true;
	LSwing = true;

	MaxDegree = 0.0f;
	AddRotation = 0.0f;
	DoorCurrentRotation = 0.0f;
	OpenAngle = -90.0f;

}

// Called when the game starts or when spawned
void ADoorSwing::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoorSwing::Tick(float DeltaTime)
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

void ADoorSwing::OpenDoor(float dt)
{
	if (LSwing)
	{
		AddRotation = -dt * 150;
	}
	else
	{
		AddRotation = dt * 150;
	}
	MaxDegree = OpenAngle;
	DoorCurrentRotation = Door->RelativeRotation.Yaw;
	if (FMath::IsNearlyEqual(DoorCurrentRotation, MaxDegree, 1.5f))
	{
		Closing = false;
		Opening = false;
	}
	else if (Opening)
	{
		FRotator NewRotation = FRotator(0.0f, AddRotation, 0.0f);
		Door->AddRelativeRotation(FQuat(NewRotation));
	}
}

void ADoorSwing::CloseDoor(float dt)
{
	if (LSwing)
	{
		AddRotation = dt * 150;
		MaxDegree = 0;
	}
	else
	{
		AddRotation = -dt * 150;
		MaxDegree = -180;
	}
	DoorCurrentRotation = Door->RelativeRotation.Yaw;
	if (FMath::IsNearlyEqual(DoorCurrentRotation, MaxDegree, 1.5f))
	{
		Closing = false;
		Opening = false;
	}
	else if (Closing)
	{
		FRotator NewRotation = FRotator(0.0f, AddRotation, 0.0f);
		Door->AddRelativeRotation(FQuat(NewRotation));
	}
}

void ADoorSwing::ToggleDoor()
{
	if (Opening || Closing)
	{
		return;
	}
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

