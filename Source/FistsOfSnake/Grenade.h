// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "FPSProjectileGrenade.h"
#include "Engine/World.h"
#include "Grenade.generated.h"

/**
 * 
 */
UCLASS()
class FISTSOFSNAKE_API AGrenade : public AItem
{
	GENERATED_BODY()

public:

	AGrenade();

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AFPSProjectileGrenade> ProjectileGrenadeClass;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	int NumberOfGrenades;

	void Use(const FVector& MuzzleLocation, const FRotator& MuzzleRotation, const FActorSpawnParameters& SpawnParams);

	void ThrowGrenade(const FVector& MuzzleLocation, const FRotator& MuzzleRotation, const FActorSpawnParameters& SpawnParams);

};
