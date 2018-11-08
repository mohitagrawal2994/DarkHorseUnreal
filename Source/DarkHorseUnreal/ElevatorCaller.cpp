// Fill out your copyright notice in the Description page of Project Settings.

#include "ElevatorCaller.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
AElevatorCaller::AElevatorCaller()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ECaller = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ECaller"));
	RootComponent = ECaller;
	ECaller->SetMobility(EComponentMobility::Static);

	Button1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button1"));
	Button1->SetupAttachment(RootComponent);
	Button1->SetMobility(EComponentMobility::Static);

	Button2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button2"));
	Button2->SetupAttachment(RootComponent);
	Button2->SetMobility(EComponentMobility::Static);

	FloorNo = 0;
	OnlyUp = false;
	OnlyDown = false;
}

// Called when the game starts or when spawned
void AElevatorCaller::BeginPlay()
{
	Super::BeginPlay();

	//Hiding buttons according to its properties and disabling collision so that ray trace cannot detect a hit to that button
	if (OnlyUp)
	{
		Button2->SetHiddenInGame(true);
		Button2->SetCollisionProfileName("NoCollision");
	}
	if (OnlyDown)
	{
		Button1->SetHiddenInGame(true);
		Button1->SetCollisionProfileName("NoCollision");
	}
	
}

// Called every frame
void AElevatorCaller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Returns the current floor at which the actor is placed
int AElevatorCaller::GetFloorNo()
{
	return FloorNo;
}

//Returns the elevator controlled by the current caller
AElevator * AElevatorCaller::GetCurrentElevator()
{
	return CurrentElevator;
}
