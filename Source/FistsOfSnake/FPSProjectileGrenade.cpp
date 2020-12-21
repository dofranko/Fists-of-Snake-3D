// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSProjectileGrenade.h"
#include "FPSCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "DestructibleActor.h"
#include "DestructibleComponent.h"
#include "Particles/ParticleSystemComponent.h"

AFPSProjectileGrenade::AFPSProjectileGrenade()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("/Game/FPS_Weapon_Bundle/Weapons/Meshes/G67_Grenade/SM_G67"));
	if (Mesh.Succeeded()) 
	{
		ProjectileMeshComponent->SetStaticMesh(Mesh.Object);
		ProjectileMeshComponent->SetRelativeScale3D(FVector(2, 2, 2));
	}

	ProjectileMovementComponent->InitialSpeed = 1500.0f;
	ProjectileMovementComponent->ProjectileGravityScale = 1.0f;

	static ConstructorHelpers::FObjectFinder<USoundCue> Sound(TEXT("'/Game/StarterContent/Audio/Explosion_Cue.Explosion_Cue'"));
	ExplosionSound = Sound.Object;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> Particle(TEXT("'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	ExplosionParticles = Particle.Object;
}

void AFPSProjectileGrenade::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != NULL) && (OtherActor != this))
		OnDetonate();
}

void AFPSProjectileGrenade::BeginPlay()
{
	Super::BeginPlay();

	// Time to explode after hitting
	FTimerHandle handle;
	World = GetWorld();
	if (World)
		World->GetTimerManager().SetTimer(handle, this, &AFPSProjectileGrenade::OnDetonate, 5.f, false);

}

void AFPSProjectileGrenade::OnDetonate()
{
	UParticleSystemComponent *Explosion = UGameplayStatics::SpawnEmitterAtLocation(World, ExplosionParticles, GetActorTransform());
	Explosion->SetRelativeScale3D(FVector(4.f));

	UGameplayStatics::PlaySoundAtLocation(World, ExplosionSound, GetActorLocation());

	TArray<FHitResult> OutHits;

	FVector StartTrace = GetActorLocation();
	FVector EndTrace = StartTrace;
	EndTrace.Z += 300.f;

	FCollisionShape CollisionShape;
	CollisionShape.ShapeType = ECollisionShape::Sphere;
	CollisionShape.SetSphere(Radius);
	
	// Ignoring hitting myself (FPSProjectileGrenade)
	FCollisionQueryParams TraceParam(FName(TEXT("TraceParam")), false, this);

	if (World->SweepMultiByChannel(OutHits, StartTrace, EndTrace, FQuat::Identity, ECC_Pawn, CollisionShape, TraceParam))
	{
		for (auto& hited : OutHits)
		{
			// Check if Actor has been destroyed
			if (hited.GetActor())
			{
				// Throw away some static mesh
				UStaticMeshComponent* SM = Cast<UStaticMeshComponent>(hited.GetActor()->GetRootComponent());
				if (SM)
					SM->AddRadialImpulse(GetActorLocation(), 1000.f, 5000.f, ERadialImpulseFalloff::RIF_Linear, true);

				// Crash some destructible mesh
				ADestructibleActor* DA = Cast<ADestructibleActor>(hited.GetActor());
				if (DA)
					DA->GetDestructibleComponent()->ApplyRadiusDamage(10.f, hited.ImpactPoint, 500.f, 3000.f, false);

				AFPSCharacter* Player = Cast<AFPSCharacter>(hited.GetActor());
				if (Player)
				{
					UPrimitiveComponent* ActorComponent = hited.GetActor()->FindComponentByClass<UPrimitiveComponent>();
					ActorComponent->AddRadialImpulse(GetActorLocation(), 1000.f, 5000.f, ERadialImpulseFalloff::RIF_Linear, true);
					Player->DamageMe(this->Damage);
				}
			}
		}
	}

	Destroy();
}