// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
		USkeletalMeshComponent* WeaponMesh;
};
