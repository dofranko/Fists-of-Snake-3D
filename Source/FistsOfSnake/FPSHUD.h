// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPSCharacter.h"
#include "GameFramework/HUD.h"
#include "Engine/Canvas.h"
#include "Kismet/GameplayStatics.h"
#include "FPSHUD.generated.h"

//Forward include
class AFPSCharacter;
class AWeapon;

/**
 * 
 */
UCLASS()
class FISTSOFSNAKE_API AFPSHUD : public AHUD
{
	GENERATED_BODY()

protected:
	// This will be drawn at the center of the screen.
	UPROPERTY(EditDefaultsOnly)
		UTexture2D *CrosshairTexture;

	UPROPERTY()
		int AmmoMagazine;

	// Snip from header.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD Font")
		UFont *FontType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD Font")
		bool bScalePosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD Font")
		FLinearColor FontColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD Font Ammunition Total")
		FVector2D PositionAmmunitionTotal;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD Font Ammunition Total")
		float FontSizeAmmunitionTotal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD Font Ammunition Magazine")
		FVector2D PositionAmmunitionMagazine;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD Font Ammunition Magazine")
		float FontSizeAmmunitionMagazine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD Font Ammunition Magazine")
		FVector2D PositionHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD Font Ammunition Magazine")
		float FontSizeHealth;


public:
	// Primary draw call for the HUD.
	virtual void DrawHUD() override;
};
