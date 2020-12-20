// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Throwable.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "FPSProjectile.generated.h"

UCLASS()
class FISTSOFSNAKE_API AFPSProjectile : public AThrowable
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	AFPSProjectile();

};
