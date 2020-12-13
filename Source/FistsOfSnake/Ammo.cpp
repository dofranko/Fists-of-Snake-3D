// Fill out your copyright notice in the Description page of Project Settings.


#include "Ammo.h"
#include "Weapon.h"

AAmmo::AAmmo()
{
	this->StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AmmoStaticMesh"));
	this->StaticMesh->SetRelativeScale3D(FVector(3, 3, 3));
	this->RootComponent = this->StaticMesh;
	this->Ammunition = 50;
}

void AAmmo::PickUp(AFPSCharacter* Player)
{
	AWeapon* PlayerWeapon = Cast<AWeapon>(Player->EquippedItem);
	if (PlayerWeapon)
	{
		if (PlayerWeapon->AmmunitionMagazine == PlayerWeapon->AmmunitionMagazineMax && PlayerWeapon->AmmunitionMax == PlayerWeapon->AmmunitionTotal)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Your weapon is full of ammo"));
			return;
		}

		if (this->Ammunition <= PlayerWeapon->AmmunitionMagazineMax - PlayerWeapon->AmmunitionMagazine)
		{
			PlayerWeapon->AmmunitionMagazine += this->Ammunition;
			this->Ammunition = 0;
		}
		else
		{
			this->Ammunition -= PlayerWeapon->AmmunitionMagazineMax - PlayerWeapon->AmmunitionMagazine;
			PlayerWeapon->AmmunitionMagazine = PlayerWeapon->AmmunitionMagazineMax;
		}

		if (this->Ammunition < PlayerWeapon->AmmunitionMax - PlayerWeapon->AmmunitionTotal)
		{
			PlayerWeapon->AmmunitionTotal += this->Ammunition;
		}
		else
		{
			PlayerWeapon->AmmunitionTotal = PlayerWeapon->AmmunitionMax;
		}

		Destroy();
	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("You have to hold some weapon"));
}