// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class DARKHORSEUNREAL_API AMyHUD : public AHUD
{
	GENERATED_BODY()
	
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

public :

	AMyHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;
	
	
};
