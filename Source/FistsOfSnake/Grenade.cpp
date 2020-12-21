// Fill out your copyright notice in the Description page of Project Settings.


#include "Grenade.h"

AGrenade::AGrenade()
{
	this->SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GrenadeSkeletalMesh"));
	this->RootComponent = this->SkeletalMesh;

	ProjectileGrenadeClass = AFPSProjectileGrenade::StaticClass();

	this->NumberOfGrenades = 10;
}

void AGrenade::Use(const FVector& MuzzleLocation, const FRotator& MuzzleRotation)
{
	check(GEngine != nullptr);
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Throwing a grenade"));
	this->ThrowGrenade(MuzzleLocation, MuzzleRotation);
	this->NumberOfGrenades -= 1;
	if (this->NumberOfGrenades == 0)
	{
		Destroy();
		this->bAlive = false;
	}	
}

void AGrenade::ThrowGrenade(const FVector& MuzzleLocation, const FRotator& MuzzleRotation)
{
	if (ProjectileGrenadeClass) {
		if (!World)
			World = GetWorld();
		if (World)
		{
			FActorSpawnParameters spawnParameters;
			spawnParameters.Owner = this;
			// Spawn the projectile at the muzzle.
			AFPSProjectileGrenade *ProjectileGrenade = World->SpawnActor<AFPSProjectileGrenade>(ProjectileGrenadeClass, MuzzleLocation, MuzzleRotation, spawnParameters);
			ProjectileGrenade->World = World;
			if (ProjectileGrenade)
			{
				// Set the projectile's initial trajectory.
				FVector LaunchDirection = (MuzzleRotation + FRotator(10.f, 0.f, 0.f)).Vector();
				ProjectileGrenade->FireInDirection(LaunchDirection);
			}
		}
	}
}