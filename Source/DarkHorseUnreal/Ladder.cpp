// Fill out your copyright notice in the Description page of Project Settings.

#include "Ladder.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "MyCharacter.h"

// Sets default values
ALadder::ALadder()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Setting properties for ladders static mesh
	Ladder = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ladder"));
	RootComponent = Ladder;
	Ladder->SetMobility(EComponentMobility::Static);

	//Setting properties for the trigger box
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(Ladder);
	TriggerBox->SetMobility(EComponentMobility::Static);
	TriggerBox->SetCollisionProfileName("Trigger");
	TriggerBox->InitBoxExtent(FVector(32, 32, 280));
	TriggerBox->SetWorldTransform(FTransform(FVector(30, 0, 280)));

	//Setting the player pointer to null
	OverlappingPlayer = NULL;

}

// Called when the game starts or when spawned
void ALadder::BeginPlay()
{
	Super::BeginPlay();
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ALadder::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ALadder::OnOverlapEnd);
}

// Called every frame
void ALadder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALadder::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if((OtherActor != nullptr) && (OtherComp != nullptr) && (OtherActor != this) && (OtherActor->GetClass()->IsChildOf(AMyCharacter::StaticClass())))
	{
		OverlappingPlayer = Cast<AMyCharacter>(OtherActor);
		OverlappingPlayer->CanClimbLadder();
	}
}

void ALadder::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if ((OtherActor != nullptr) && (OtherComp != nullptr) && (OtherActor != this))
	{
		OverlappingPlayer = Cast<AMyCharacter>(OtherActor);
		OverlappingPlayer->CannotClimbLadder();
		OverlappingPlayer = NULL;
	}
}

