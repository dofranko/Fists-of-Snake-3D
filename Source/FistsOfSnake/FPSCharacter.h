// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Camera/PlayerCameraManager.h"
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

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float MaxHealth;

	UPROPERTY(ReplicatedUsing = OnRep_CurrentHealth)
	float CurrentHealth;

	UFUNCTION()
	void OnRep_CurrentHealth();

	/** Response to health being updated. Called on the server immediately after modification, and on clients in response to a RepNotify*/
	void OnHealthUpdate();

public:
	/** Property replication */
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const override;

	/** Getter for Max Health.*/
	UFUNCTION(BlueprintPure, Category = "Health")
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }

	/** Getter for Current Health.*/
	UFUNCTION(BlueprintPure, Category = "Health")
	FORCEINLINE float GetCurrentHealth() const { return CurrentHealth; }

	/** Setter for Current Health. Clamps the value between 0 and MaxHealth and calls OnHealthUpdate. Should only be called on the server.*/
	UFUNCTION(BlueprintCallable, Category = "Health")
	void SetCurrentHealth(float healthValue);

	/** Event for taking damage. Overridden from APawn.*/
	UFUNCTION(BlueprintCallable, Category = "Health")
	float TakeDamage(float DamageTaken, struct FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser) override;

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
	UFUNCTION(Server, Reliable)
	void UseItem();

	// Gun muzzle offset from the camera location.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	// Actualy used item in hands
	UPROPERTY(ReplicatedUsing = SpawnFirstWeapon1, EditDefaultsOnly, Category = Item)
	AItem *EquippedItem;

	UFUNCTION(BlueprintPure, Category = Weapon)
	AItem *GetEquippedItem();

	int EquippedItemIndex = -1;

	// Change jump flag when key is pressed.
	UFUNCTION()
	void PlayerJump();

	//Tries to Reload weapon
	UFUNCTION(Server, Reliable)
	void Reload();

	UFUNCTION(Server, Reliable)
	void SpawnFirstWeapon();

	UFUNCTION()
	void SpawnFirstWeapon1();

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
	float GetHealth();

	UPROPERTY(VisibleAnywhere)
	bool bAlive;

	void SetWantToPickUp();

	bool bHasCollisionWithItem = false;

	bool bWantToPickUp = false;

	void ThrowItem();

	void ChooseItem(int index);

	void DamageMe(int damage);

	Inventory *MyInventory;

	const APlayerCameraManager *ManagerCamera;
};
