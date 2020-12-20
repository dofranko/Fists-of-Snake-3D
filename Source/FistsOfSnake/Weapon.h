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
	
public:

	AWeapon();

	// Projectile class to spawn.
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AFPSProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	int AmmunitionMax;
	
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	int AmmunitionMagazineMax;

	UPROPERTY()
	int AmmunitionTotal;

	UPROPERTY()
	int AmmunitionMagazine;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	float ReloadTime;

	bool bReloading;

	
	
	void Fire(const FVector& MuzzleLocation, const FRotator& MuzzleRotation);

	void Use(const FVector& MuzzleLocation, const FRotator& MuzzleRotation, const FActorSpawnParameters& SpawnParams);

	void StartReloading();

	void StopReloading();

	void Reload();

private:
	FTimerHandle _reloadTimerHandler;
};
