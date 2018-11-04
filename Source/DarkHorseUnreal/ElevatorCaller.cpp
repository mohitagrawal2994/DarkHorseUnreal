// Fill out your copyright notice in the Description page of Project Settings.

#include "ElevatorCaller.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
AElevatorCaller::AElevatorCaller()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ECaller = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ECaller"));
	RootComponent = ECaller;
	ECaller->SetMobility(EComponentMobility::Static);

	Button1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button1"));
	Button1->SetupAttachment(RootComponent);
	Button1->SetMobility(EComponentMobility::Static);

	Button2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button2"));
	Button2->SetupAttachment(RootComponent);
	Button2->SetMobility(EComponentMobility::Static);
}

// Called when the game starts or when spawned
void AElevatorCaller::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AElevatorCaller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

