// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"


AWeapon::AWeapon()
{

	this->SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponSkeletalMesh"));
	this->RootComponent = this->SkeletalMesh;

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
}


void AWeapon::Use_Implementation(const FVector& MuzzleLocation, const FRotator& MuzzleRotation) {
	check(GEngine != nullptr);
	if (bReloading) {
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Reloading"));
	}
	else if (CurrentAmmunitionMagazine <= 0 && CurrentAmmunitionTotal <= 0) {
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("No ammo"));
	}
	else if (CurrentAmmunitionMagazine <= 0) {
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Need to reload"));
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
			
			spawnParameters.Owner = this;
			AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, spawnParameters);
			if (Projectile)
			{
				// Set the projectile's initial trajectory.
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
			}
		}
		CurrentAmmunitionMagazine--;
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("Shooting. I Have %d ammo"), CurrentAmmunitionMagazine));
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
	
		bReloading = true;
		GetWorld()->GetTimerManager().SetTimer(_reloadTimerHandler, this, &AWeapon::Reload, ReloadTime, false);
	
}

void AWeapon::StopReloading() {
	bReloading = false;
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
