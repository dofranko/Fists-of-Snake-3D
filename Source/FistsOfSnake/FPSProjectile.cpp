// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSProjectile.h"
#include "FPSCharacter.h"

AFPSProjectile::AFPSProjectile()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("'/Game/StarterContent/Props/MaterialSphere.MaterialSphere'"));
	if (Mesh.Succeeded())
		ProjectileMeshComponent->SetStaticMesh(Mesh.Object);

	static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("'/Game/Materials/SphereMaterial.SphereMaterial'"));
	if (Material.Succeeded())
	{
		ProjectileMaterialInstance = UMaterialInstanceDynamic::Create(Material.Object, ProjectileMeshComponent);
		ProjectileMeshComponent->SetMaterial(0, ProjectileMaterialInstance);
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> DefaultExplosionEffect(TEXT("/Game/StarterContent/Particles/P_Explosion.P_Explosion"));
	if (DefaultExplosionEffect.Succeeded())
	{
		ExplosionEffect = DefaultExplosionEffect.Object;
	}

	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
}

