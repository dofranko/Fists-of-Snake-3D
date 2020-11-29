// Fill out your copyright notice in the Description page of Project Settings.

#include "Item.h"
#include <Runtime\Engine\Classes\Kismet\KismetSystemLibrary.h>
#include <Runtime\Engine\Public\DrawDebugHelpers.h>

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->RotationRate = FRotator(0.0f, 180.0f, 0.0f);
	this->RotationSpeed = 1.0f;
	this->SetActorEnableCollision(false);
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Rotate the object
	this->AddActorLocalRotation(this->RotationRate * DeltaTime * RotationSpeed);

	for (auto& Player : this->Players)
	{
		FVector PlayerLocation = Player->GetActorLocation();
		FVector Distance = PlayerLocation - this->GetActorLocation();

		// When there is collision with someone
		if (Distance.Size() < 100)
		{
			FString PickUpMessage = FString::Printf(TEXT("Press G to pickup %s"), *ItemName);
			DrawDebugString(GetWorld(), this->GetActorLocation(),
				PickUpMessage, nullptr, FColor::Green, 0.0f, true);
			if (Player->bWantToPickUp)
				PickUp(Player);
		}
	}
	
}

void AItem::PickUp(AFPSCharacter* Player)
{
	if (Player->MyInventory->AddItem(this))
	{
		HideOrExposeMe(true);
	}
}

void AItem::HideOrExposeMe(bool bFlag)
{
	SetActorHiddenInGame(bFlag);
	SetActorTickEnabled(!bFlag);
}

void AItem::ThrowMe(AFPSCharacter* Player)
{
	FVector PlayerLocation = Player->GetActorLocation();
	FVector PlayerForwardVector = Player->GetActorForwardVector();
	this->SetActorLocation(PlayerLocation + PlayerForwardVector*200);
	HideOrExposeMe(false);
}