// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FPSCharacter.h"
#include "Inventory.h"
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

	/** Property replication */
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	// Object's name
	UPROPERTY(Replicated, BlueprintReadOnly, Category = Item)
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
		USkeletalMeshComponent* SkeletalMesh;

	// Object rotation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
		FRotator RotationRate;

	// Rotation speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
		float RotationSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Icon)
		UTexture2D* ItemIcon;
	
	// Array of players
	TArray<AFPSCharacter*> Players;

	// Flag informs if item was destroyed
	bool bAlive = true;

	// When collision was detected
	void OnCollision(AFPSCharacter* Player);

	// To pick up an item
	virtual void PickUp(AFPSCharacter* Player);

	// When an item is picked up it has to disappear
	void HideOrExposeMe(bool bFlag);

	// To throw an item in front of a player
	void ThrowMe(AFPSCharacter* Player);

	// Activate an item
	
	virtual void Use(const FVector& MuzzleLocation, const FRotator& MuzzleRotation);

	// Reload a weapon
	virtual void Reload();

};