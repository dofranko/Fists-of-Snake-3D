// Fill out your copyright notice in the Description page of Project Settings.


#include "Grenade.h"

AGrenade::AGrenade()
{
	this->SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GrenadeSkeletalMesh"));
	this->RootComponent = this->SkeletalMesh;

	ProjectileGrenadeClass = AFPSProjectileGrenade::StaticClass();

	this->NumberOfGrenades = 10;
}

void AGrenade::Use(const FVector& MuzzleLocation, const FRotator& MuzzleRotation, FActorSpawnParameters SpawnParams)
{
	check(GEngine != nullptr);
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Throwing a grenade"));
	this->ThrowGrenade(MuzzleLocation, MuzzleRotation, SpawnParams);
	this->NumberOfGrenades -= 1;
	if (this->NumberOfGrenades == 0)
	{
		Destroy();
		this->bAlive = false;
	}	
}

void AGrenade::ThrowGrenade(const FVector& MuzzleLocation, const FRotator& MuzzleRotation, FActorSpawnParameters SpawnParams)
{
	if (ProjectileGrenadeClass) {
		UWorld* World = GetWorld();
		if (World)
		{
			// Spawn the projectile at the muzzle.
			AFPSProjectileGrenade *ProjectileGrenade = World->SpawnActor<AFPSProjectileGrenade>(ProjectileGrenadeClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (ProjectileGrenade)
			{
				// Set the projectile's initial trajectory.
				FVector LaunchDirection = (MuzzleRotation + FRotator(10.f, 0.f, 0.f)).Vector();
				ProjectileGrenade->FireInDirection(LaunchDirection);
			}
		}
	}
}