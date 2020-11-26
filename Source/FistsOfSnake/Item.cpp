// Fill out your copyright notice in the Description page of Project Settings.

#include "Item.h"
#include <Runtime\Engine\Classes\Kismet\KismetSystemLibrary.h>
#include <Runtime\Engine\Public\DrawDebugHelpers.h>

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	this->RootComponent = SceneComponent;
	this->RotationRate = FRotator(0.0f, 180.0f, 0.0f);
	this->RotationSpeed = 1.0f;
	
	//create collider
	this->BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	this->BoxCollider->SetGenerateOverlapEvents(true);
	this->BoxCollider->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	this->BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnOverlapBegin);
	this->BoxCollider->OnComponentEndOverlap.AddDynamic(this, &AItem::OnOverlapEnd);
	this->BoxCollider->AttachToComponent(this->RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
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

	//obracaj obiekt
	
	this->AddActorLocalRotation(this->RotationRate * DeltaTime * RotationSpeed);

	// gdy gracz ma kolizjê z tym przedmiotem
	if (this->bItemWithinRange == true)
	{
		FString PickUpMessage = FString::Printf(TEXT("Press G to pickup %s"), *ItemName);
		DrawDebugString(GetWorld(), this->RootComponent->GetComponentLocation(), 
			PickUpMessage, nullptr, FColor::Green, 0.3f, true);

		if (this->Player != NULL && this->Player->bWantToPickUp)
		{
			PickUp();
			this->Player->bWantToPickUp = false;
		}
	}
}

void AItem::PickUp()
{
	//this->Player->Inventory.Add(*ItemName);
	Destroy();
}

void AItem::OnOverlapBegin(class UPrimitiveComponent* OverlappedComponent, 
	class AActor* OtherActor, 
	class UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		this->bItemWithinRange = true;
		this->Player = Cast<AFPSCharacter>(OtherActor);
	}
	
}

void AItem::OnOverlapEnd(class UPrimitiveComponent* OverlappedComponent, 
	class AActor* OtherActor, 
	class UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex)
{
	this->bItemWithinRange = false;
	this->Player = NULL;
}

void AItem::Use(const FVector& MuzzleLocation, const FRotator& MuzzleRotation, FActorSpawnParameters SpawnParams)
{

}

void AItem::Reload() {

}