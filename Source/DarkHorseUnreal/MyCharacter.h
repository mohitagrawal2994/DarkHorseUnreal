// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class DARKHORSEUNREAL_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	//Creating a variable to get the default capsule component
	UPROPERTY(VisibleAnywhere, Category = "Capsule")
	class UCapsuleComponent* CollisionCapsule;

	//Creating a variable to hold the current overlapped door actor
	class ADoorSwing* CurrentDoor;

	//Creating a variable to hold the current overlapped door actor
	class ADoorSwingReliance* RelDoor;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Handles moving forward/backward
	void MoveForward(float Val);

	//Handles stafing movement, left and right
	void MoveRight(float Val);

	//Handles the input for door closing/opening
	void DoorAction();

public:	
	// Sets default values for this character's properties
	AMyCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
};
