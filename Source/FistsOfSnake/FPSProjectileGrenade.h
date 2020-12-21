// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Throwable.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundCue.h"
#include "FPSProjectileGrenade.generated.h"

/**
 * 
 */
UCLASS()
class FISTSOFSNAKE_API AFPSProjectileGrenade : public AThrowable
{
	GENERATED_BODY()

public:

	// Sets default values for this actor's properties
	AFPSProjectileGrenade();

protected:

	// Called when the game starts or when spawned
	void BeginPlay();

public:

	UPROPERTY(EditAnywhere, Category = "FX")
	class UParticleSystem* ExplosionParticles;

	UPROPERTY(EditAnywhere, Category = "FX")
	class USoundCue* ExplosionSound;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	float Radius = 500.f;

	UWorld* World;

	UFUNCTION()
	void OnDetonate();

	// Function that is called when the projectile hits something.
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

};
