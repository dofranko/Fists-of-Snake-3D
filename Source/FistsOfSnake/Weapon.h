// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Item.h"
#include "FPSProjectile.h"
#include "Net/UnrealNetwork.h"
#include "Weapon.generated.h"


/**
 * 
 */
UCLASS()
class FISTSOFSNAKE_API AWeapon : public AItem
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category = Ammo)
	int MaxAmmunitionTotal;

	UPROPERTY(EditDefaultsOnly, Category = Ammo)
	int MaxAmmunitionMagazine;

	UPROPERTY(ReplicatedUsing=OnRep_CurrentAmmunitionTotal)
	int CurrentAmmunitionTotal;

	UPROPERTY(ReplicatedUsing=OnRep_CurrentAmmunitionMagazine)
	int CurrentAmmunitionMagazine;

	UFUNCTION()
	void OnRep_CurrentAmmunitionTotal();

	UFUNCTION()
	void OnRep_CurrentAmmunitionMagazine();

public:

	AWeapon();

	/** Property replication */
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/** Getter for Current Ammo in magazine.*/
	UFUNCTION(BlueprintPure, Category = "Ammo")
	FORCEINLINE int GetCurrentAmmunitionMagazine() const { return CurrentAmmunitionMagazine; }

	/** Getter for Current Ammo in total.*/
	UFUNCTION(BlueprintPure, Category = "Ammo")
	FORCEINLINE int GetCurrentAmmunitionTotal() const { return CurrentAmmunitionTotal; }

	/** Getter for Max Ammo in magazine.*/
	UFUNCTION(BlueprintPure, Category = "Ammo")
	FORCEINLINE int GetMaxAmmunitionMagazine() const { return MaxAmmunitionMagazine; }

	/** Getter for Max Ammo in total.*/
	UFUNCTION(BlueprintPure, Category = "Ammo")
	FORCEINLINE int GetMaxAmmunitionTotal() const { return MaxAmmunitionTotal; }

	/** Getter for Max Ammo in magazine.*/
	UFUNCTION(Category = "Ammo")
	void SetCurrentAmmunitionMagazine(int ammo);

	/** Getter for Max Ammo in total.*/
	UFUNCTION(Category = "Ammo")
	void SetCurrentAmmunitionTotal(int ammo);

	// Projectile class to spawn.
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AFPSProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	float ReloadTime;

	bool bReloading;
	
	UFUNCTION(Server, Reliable)
	void Fire(const FVector& MuzzleLocation, const FRotator& MuzzleRotation);

	UFUNCTION(Server, Reliable)
	void Use(const FVector& MuzzleLocation, const FRotator& MuzzleRotation);

	void StartReloading();

	void StopReloading();

	UFUNCTION(Server, Reliable)
	void Reload();

private:
	FTimerHandle _reloadTimerHandler;
};
