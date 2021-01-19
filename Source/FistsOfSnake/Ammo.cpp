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

void AAmmo::PickUp(AFPSCharacter *Player)
{
	AWeapon *PlayerWeapon = Cast<AWeapon>(Player->EquippedItem);
	if (PlayerWeapon)
	{
		if (PlayerWeapon->GetCurrentAmmunitionMagazine() == PlayerWeapon->GetMaxAmmunitionMagazine() && PlayerWeapon->GetMaxAmmunitionTotal() == PlayerWeapon->GetCurrentAmmunitionTotal())
		{
			return;
		}

		if (this->Ammunition <= PlayerWeapon->GetMaxAmmunitionMagazine() - PlayerWeapon->GetCurrentAmmunitionMagazine())
		{
			PlayerWeapon->SetCurrentAmmunitionMagazine(PlayerWeapon->GetCurrentAmmunitionMagazine() + this->Ammunition);
			this->Ammunition = 0;
		}
		else
		{
			this->Ammunition -= PlayerWeapon->GetMaxAmmunitionMagazine() - PlayerWeapon->GetCurrentAmmunitionMagazine();
			PlayerWeapon->SetCurrentAmmunitionMagazine(PlayerWeapon->GetMaxAmmunitionMagazine());
		}

		if (this->Ammunition < PlayerWeapon->GetMaxAmmunitionTotal() - PlayerWeapon->GetCurrentAmmunitionTotal())
		{
			PlayerWeapon->SetCurrentAmmunitionTotal(PlayerWeapon->GetCurrentAmmunitionTotal() + this->Ammunition);
		}
		else
		{
			PlayerWeapon->SetCurrentAmmunitionTotal(PlayerWeapon->GetMaxAmmunitionTotal());
		}

		Destroy();
	}
}