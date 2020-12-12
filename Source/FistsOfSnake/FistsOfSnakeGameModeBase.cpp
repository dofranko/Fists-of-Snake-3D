// Copyright Epic Games, Inc. All Rights Reserved.

#include "FistsOfSnakeGameModeBase.h"
#include <Runtime\Engine\Public\EngineUtils.h>
#include "Weapon.h"
#include "Grenade.h"
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>

void AFistsOfSnakeGameModeBase::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr);

	// Display a debug message for five seconds.
	// The -1 "Key" value argument prevents the message from being updated or refreshed.
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, this is FPSGameMode!"));


	// ATTENTION: everything below is temporary before we will make random generating

	const TCHAR *SkeletalPath = TEXT("/Game/FPS_Weapon_Bundle/Weapons/Meshes/AR4");
	const TCHAR *SkeletalPath2 = TEXT("/Game/FPS_Weapon_Bundle/Weapons/Meshes/Ka47");
	const TCHAR* SkeletalPath3 = TEXT("/Game/FPS_Weapon_Bundle/Weapons/Meshes/G67_Grenade");
	const TCHAR *Texture2DPath = TEXT("/Game/FPS_Weapon_Bundle/Icons");

	FActorSpawnParameters SpawnInfo;
	// Not spawn if it is collision
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;
	FVector SpawnLocation(-190.0f, 30.0f, 120.0f);
	FRotator Rotation(-25.0f, 0.0f, 0.0f);
	AWeapon *Weapon1 = GetWorld()->SpawnActor<AWeapon>(AWeapon::StaticClass(), SpawnLocation, Rotation, SpawnInfo);
	FVector SpawnLocation1(-130.0f, 30.0f, 120.0f);
	AWeapon *Weapon2 = GetWorld()->SpawnActor<AWeapon>(AWeapon::StaticClass(), SpawnLocation1, Rotation, SpawnInfo);
	FVector SpawnLocation2(-150.0f, 60.0f, 120.0f);
	AGrenade *Grenade = GetWorld()->SpawnActor<AGrenade>(AGrenade::StaticClass(), SpawnLocation2, Rotation, SpawnInfo);

	TArray<UObject *> Array;
	EngineUtils::FindOrLoadAssetsByPath(SkeletalPath, Array, EngineUtils::ATL_Regular);
	USkeletalMesh *SkeletalMesh = Cast<USkeletalMesh>(Array[0]);
	Weapon1->SkeletalMesh->SetSkeletalMesh(SkeletalMesh);
	Weapon1->ItemName = FString(TEXT("AR4"));

	TArray<UObject*> Array2;
	EngineUtils::FindOrLoadAssetsByPath(SkeletalPath2, Array2, EngineUtils::ATL_Regular);
	USkeletalMesh* SkeletalMesh2 = Cast<USkeletalMesh>(Array2[0]);
	Weapon2->SkeletalMesh->SetSkeletalMesh(SkeletalMesh2);
	Weapon2->ItemName = FString(TEXT("Ka47"));

	TArray<UObject*> Array3;
	EngineUtils::FindOrLoadAssetsByPath(SkeletalPath3, Array3, EngineUtils::ATL_Regular);
	USkeletalMesh* SkeletalMesh3 = Cast<USkeletalMesh>(Array3[0]);
	Grenade->SkeletalMesh->SetSkeletalMesh(SkeletalMesh3);
	Grenade->ItemName = FString(TEXT("G67"));

	TArray<UObject*> Array4;
	EngineUtils::FindOrLoadAssetsByPath(Texture2DPath, Array4, EngineUtils::ATL_Regular);
	UTexture2D *texture = Cast<UTexture2D>(Array4[2]);
	Weapon1->ItemIcon = texture;
	texture = Cast<UTexture2D>(Array4[1]);
	Weapon2->ItemIcon = texture;
	texture = Cast<UTexture2D>(Array4[0]);
	Grenade->ItemIcon = texture;

	AFPSCharacter* mainPlayer = Cast<AFPSCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (mainPlayer != nullptr)
	{
		Weapon1->Players.Add(mainPlayer);
		Weapon2->Players.Add(mainPlayer);
		Grenade->Players.Add(mainPlayer);
	}
		
}