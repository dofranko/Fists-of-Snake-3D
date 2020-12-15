// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Ammo.generated.h"

/**
 * 
 */
UCLASS()
class FISTSOFSNAKE_API AAmmo : public AItem
{
	GENERATED_BODY()

public:

	AAmmo();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	UStaticMeshComponent* StaticMesh;

	// Amount of ammo
	int Ammunition;

	// When player want to pick up ammo
	void PickUp(AFPSCharacter* Player);
	
};
