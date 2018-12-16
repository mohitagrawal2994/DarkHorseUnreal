// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ladder.generated.h"

UCLASS()
class DARKHORSEUNREAL_API ALadder : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly)					//Creating a pointer of type static mesh
	class UStaticMeshComponent* Ladder;

	UPROPERTY(VisibleDefaultsOnly)					//Creating a pointer of type box component
	class UBoxComponent* TriggerBox;

	class AMyCharacter* OverlappingPlayer;

	
public:	
	// Sets default values for this actor's properties
	ALadder();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex);

};
