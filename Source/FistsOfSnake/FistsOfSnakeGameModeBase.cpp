// Copyright Epic Games, Inc. All Rights Reserved.

#include "FistsOfSnakeGameModeBase.h"
#include <Runtime\Engine\Public\EngineUtils.h>
#include "Weapon.h"

void AFistsOfSnakeGameModeBase::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr);

	// Display a debug message for five seconds.
	// The -1 "Key" value argument prevents the message from being updated or refreshed.
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, this is FPSGameMode!"));

	// �cie�ka do mesha
	const TCHAR *SkeletalPath = TEXT("/Game/FPS_Weapon_Bundle/Weapons/Meshes/AR4");
	FActorSpawnParameters SpawnInfo;
	// nie b�dzie spawnowa�o aktor�w, kt�rzy maj� kolizj�
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;
	FVector SpawnLocation(-190.0f, 30.0f, 120.0f);
	FRotator Rotation(-25.0f, 0.0f, 0.0f);
	AWeapon *Weapon1 = GetWorld()->SpawnActor<AWeapon>(AWeapon::StaticClass(), SpawnLocation, Rotation, SpawnInfo);
	FVector SpawnLocation1(-130.0f, 30.0f, 120.0f);
	FRotator Rotation1(-25.0f, 0.0f, 0.0f);
	AWeapon *Weapon2 = GetWorld()->SpawnActor<AWeapon>(AWeapon::StaticClass(), SpawnLocation1, Rotation1, SpawnInfo);
	TArray<UObject *> Array;
	EngineUtils::FindOrLoadAssetsByPath(SkeletalPath, Array, EngineUtils::ATL_Regular);
	USkeletalMesh *SkeletalMesh = Cast<USkeletalMesh>(Array[0]);
	Weapon1->WeaponMesh->SetSkeletalMesh(SkeletalMesh);
	Weapon2->WeaponMesh->SetSkeletalMesh(SkeletalMesh);
	Weapon1->SetActorEnableCollision(false);
	Weapon2->SetActorEnableCollision(false);
}