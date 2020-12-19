// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"


AWeapon::AWeapon()
{

	this->SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponSkeletalMesh"));
	this->RootComponent = this->SkeletalMesh;

	if (!ProjectileClass) {
		ProjectileClass = AFPSProjectile::StaticClass();
	}

	if (!AmmunitionMax || AmmunitionMax <= 0) {
		AmmunitionMax = 120;
	}
	if (!AmmunitionMagazineMax || AmmunitionMagazineMax <= 0) {
		AmmunitionMagazineMax = 30;
	}
	if (!ReloadTime || ReloadTime <= 0) {
		ReloadTime = 3.f;
	}
	AmmunitionTotal = AmmunitionMax;
	AmmunitionMagazine = AmmunitionMagazineMax;
	bReloading = false;
	bReplicates = true;
}


void AWeapon::Use(const FVector& MuzzleLocation, const FRotator& MuzzleRotation, const FActorSpawnParameters& SpawnParams) {
	check(GEngine != nullptr);
	if (bReloading) {
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Reloading"));
	}
	else if (AmmunitionMagazine <= 0 && AmmunitionTotal <= 0) {
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("No ammo"));
	}
	else if (AmmunitionMagazine <= 0) {
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Need to reload"));
	}
	else {
		this->Fire(MuzzleLocation, MuzzleRotation);
		AmmunitionMagazine--;
	}
}
void AWeapon::Fire(const FVector& MuzzleLocation, const FRotator& MuzzleRotation) {
	if (ProjectileClass) {
		UWorld* World = GetWorld();
		if (World)
		{
			check(GEngine != nullptr);
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Shooting"));
			// Spawn the projectile at the muzzle.
			FActorSpawnParameters spawnParameters;
			
			spawnParameters.Owner = this;
			AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, spawnParameters);
			if (Projectile)
			{
				// Set the projectile's initial trajectory.
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
			}
		}
	}
}

void AWeapon::Reload() {
	if (!bReloading && AmmunitionMagazine < AmmunitionMagazineMax && AmmunitionTotal > 0) {
		StartReloading();
	}
}

void AWeapon::StartReloading() {
	bReloading = true;
	GetWorld()->GetTimerManager().SetTimer(_reloadTimerHandler, this, &AWeapon::StopReloading, ReloadTime, false);
}

void AWeapon::StopReloading() {
	bReloading = false;
	int toReload = AmmunitionMagazineMax - AmmunitionMagazine;
	if (AmmunitionTotal >= toReload) {
		AmmunitionTotal -= toReload;
		AmmunitionMagazine += toReload;
	}
	else {
		toReload = AmmunitionTotal;
		AmmunitionTotal -= toReload;
		AmmunitionMagazine += toReload;
	}
}

