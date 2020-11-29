// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FPSCharacter.h"
#include "Inventory.h"
#include <Runtime\Engine\Classes\Components\BoxComponent.h>
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class FISTSOFSNAKE_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Object's name
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
		USkeletalMeshComponent* SkeletalMesh;

	// Object rotation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
		FRotator RotationRate;

	// Rotation speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
		float RotationSpeed;

	// Array of players
	TArray<AFPSCharacter*> Players;

	// To pick up an item
	void PickUp(AFPSCharacter* Player);

	// When an item is picked up it has to disappear
	void HideOrExposeMe(bool bFlag);

	// To throw an item in front of a player
	void ThrowMe(AFPSCharacter* Player);

};