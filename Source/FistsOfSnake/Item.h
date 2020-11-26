// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FPSCharacter.h"
#include <Runtime\Engine\Classes\Components\BoxComponent.h>
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class FISTSOFSNAKE_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// nazwa obiektu
	UPROPERTY(EditAnywhere)
		FString ItemName = FString(TEXT(""));

	// nazwa mesha
	UPROPERTY(EditAnywhere)
		FString MeshName = FString(TEXT(""));

	// rotacja obiektu
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
		FRotator RotationRate;

	// prêdkoœæ rotacji
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
		float RotationSpeed;

	// SceneComponent jest rootem obiektów
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
		USceneComponent* SceneComponent;

	// nak³adka na obiekt, by wykrywaæ kolizjê
	UPROPERTY(EditAnywhere)
		UBoxComponent* BoxCollider;

	void PickUp();

	AFPSCharacter* Player;

	bool bItemWithinRange = false;

	//TODO obiekt playera

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComponent, 
			class AActor* OtherActor, 
			class UPrimitiveComponent* OtherComp, 
			int32 OtherBodyIndex, 
			bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComponent, 
			class AActor* OtherActor, 
			class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);

};