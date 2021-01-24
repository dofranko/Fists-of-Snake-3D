// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"


AWeapon::AWeapon()
{

	this->SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponSkeletalMesh"));
	this->RootComponent = this->SkeletalMesh;
	PrimaryActorTick.bCanEverTick = true;
	if (!ProjectileClass) {
		ProjectileClass = AFPSProjectile::StaticClass();
	}

	if (!MaxAmmunitionTotal || MaxAmmunitionTotal <= 0) {
		MaxAmmunitionTotal = 120;
	}
	if (!MaxAmmunitionMagazine || MaxAmmunitionMagazine <= 0) {
		MaxAmmunitionMagazine = 30;
	}
	if (!ReloadTime || ReloadTime <= 0) {
		ReloadTime = 3.f;
	}
	CurrentAmmunitionTotal = MaxAmmunitionTotal;
	CurrentAmmunitionMagazine = MaxAmmunitionMagazine;
	bReloading = false;
	bReplicates = true;
	SetReplicateMovement( true);
	AmmoState = 0;
}


void AWeapon::Use_Implementation(const FVector& MuzzleLocation, const FRotator& MuzzleRotation) {
	check(GEngine != nullptr);
	if (bReloading) {
		
	}
	else if (CurrentAmmunitionMagazine <= 0 && CurrentAmmunitionTotal <= 0) {
		AmmoState = 2;
	}
	else if (CurrentAmmunitionMagazine <= 0) {
		AmmoState = 3;
	}
	else {
		this->Fire(MuzzleLocation, MuzzleRotation);
	}
}
void AWeapon::Fire_Implementation(const FVector& MuzzleLocation, const FRotator& MuzzleRotation) {
	if (ProjectileClass) {
		UWorld* World = GetWorld();
		if (World)
		{
			check(GEngine != nullptr);
			// Spawn the projectile at the muzzle.
			FActorSpawnParameters spawnParameters;
			
			spawnParameters.Owner = GetOwner();
			AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, spawnParameters);
			if (Projectile)
			{
				// Set the projectile's initial trajectory.
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
			}
		}
		CurrentAmmunitionMagazine--;
	}
}

void AWeapon::Reload_Implementation() {
	int toReload = MaxAmmunitionMagazine - CurrentAmmunitionMagazine;
	if (CurrentAmmunitionTotal >= toReload) {
		CurrentAmmunitionTotal -= toReload;
		CurrentAmmunitionMagazine += toReload;
	}
	else {
		toReload = CurrentAmmunitionTotal;
		CurrentAmmunitionTotal -= toReload;
		CurrentAmmunitionMagazine += toReload;
	}
}

void AWeapon::StartReloading() {
	
	if (!bReloading) {
		bReloading = true;
		AmmoState = 1;
		GetWorld()->GetTimerManager().SetTimer(_reloadTimerHandler, this, &AWeapon::StopReloading, ReloadTime, false);
	}
	
}

void AWeapon::StopReloading() {
	bReloading = false;
	AmmoState = 0;
	Reload();
}




//////////////////////////////////////////////////////////////////////////
// Replicated Properties

void AWeapon::GetLifetimeReplicatedProps(TArray <FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//Replicate current health.
	DOREPLIFETIME(AWeapon, CurrentAmmunitionMagazine); 
	DOREPLIFETIME(AWeapon, CurrentAmmunitionTotal);
	DOREPLIFETIME(AWeapon, AmmoState);
}

void AWeapon::SetCurrentAmmunitionMagazine(int ammo) {
	if (GetLocalRole() == ROLE_Authority)
	{
		CurrentAmmunitionMagazine = ammo;

	}
}

void AWeapon::SetCurrentAmmunitionTotal(int ammo) {
	if (GetLocalRole() == ROLE_Authority)
	{
		CurrentAmmunitionTotal = ammo;
	}
}
void AWeapon::OnRep_CurrentAmmunitionTotal() {

}
void AWeapon::OnRep_CurrentAmmunitionMagazine() {

}
