// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "FPSCharacter.generated.h"

//Forward include
class AWeapon;
class AItem;
class Inventory;

UCLASS()
class FISTSOFSNAKE_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	int Health;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	// Handles input for moving forward and backward.
	UFUNCTION()
	void MoveForward(float Value);

	// Handles input for moving right and left.
	UFUNCTION()
	void MoveRight(float Value);

	// Function that handles firing projectiles.
	UFUNCTION()
	void UseItem();

	// Gun muzzle offset from the camera location.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	// Actualy used item in hands
	UPROPERTY(EditDefaultsOnly, Category = Item)
	AItem *EquippedItem;
	int EquippedItemIndex = -1;

	// Change jump flag when key is pressed.
	UFUNCTION()
	void PlayerJump();

	//Tries to Reload weapon
	UFUNCTION()
	void Reload();

	// FPS camera.
	UPROPERTY(VisibleAnywhere)
	UCameraComponent *FPSCameraComponent;

	// First-person mesh (arms), visible only to the owning player.
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent *FPSMesh;

	// First-person mesh (arms), visible only to the owning player.
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent *WeaponMesh;
	
	UFUNCTION()
	int GetHealth();
	
	UPROPERTY(VisibleAnywhere)
	bool bAlive;

	void SetWantToPickUp();

	bool bWantToPickUp = false;

	void ThrowItem();

	void ChooseItem(int index);

	void DamageMe(int damage);

	Inventory *MyInventory;

};
