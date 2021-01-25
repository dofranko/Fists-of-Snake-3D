// Fill out your copyright notice in the Description page of Project Settings.

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationEditorCommon.h"
#include <Runtime\Engine\Public\EngineUtils.h>
#include "FistsOfSnake/Item.h"
#include "FistsOfSnake/Grenade.h"
#include "FistsOfSnake/Weapon.h"
#include "FistsOfSnake/FPSCharacter.h"
#include <Editor/UnrealEd/Public/Editor.h>

#if WITH_DEV_AUTOMATION_TESTS

DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FAttackCommand, FAutomationTestBase*, test);

bool FAttackCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())//if not, everything would be made while the map is loading and the PIE is in progress.
	{
		return false;
	}

	UWorld* testWorld = GEditor->GetPIEWorldContext()->World();

	AFPSCharacter* Player = testWorld->SpawnActor<AFPSCharacter>(AFPSCharacter::StaticClass(), FVector(-180.0f, 30.0f, 120.0f), FRotator(0.f, 0.f, 0.f));
	AFPSCharacter* Player2 = testWorld->SpawnActor<AFPSCharacter>(AFPSCharacter::StaticClass(), FVector(-200.0f, 30.0f, 120.0f), FRotator(0.f, 0.f, 0.f));
	AItem* Weapon = testWorld->SpawnActor<AWeapon>(AWeapon::StaticClass(), FVector(-180.0f, 30.0f, 120.0f), FRotator(0.f, 0.f, 0.f));
	TArray<UObject*> Array;
	EngineUtils::FindOrLoadAssetsByPath(TEXT("/Game/FPS_Weapon_Bundle/Weapons/Meshes/AR4"), Array, EngineUtils::ATL_Regular);
	USkeletalMesh* SkeletalMesh = Cast<USkeletalMesh>(Array[0]);
	Weapon->SkeletalMesh->SetSkeletalMesh(SkeletalMesh);
	Weapon->PickUp(Player);
	Player->ChooseItem(0);
	int HealthBefore = Player2->GetHealth();
	Player->UseItem();
	int HealthAfter = Player2->GetHealth();
	if (HealthBefore == HealthAfter)
		test->AddError("Health of player doesn't change");
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAttackTest, "AttackTest", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAttackTest::RunTest(const FString& Parameters)
{
	{
		ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

		ADD_LATENT_AUTOMATION_COMMAND(FAttackCommand(this));

		ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	}

	return true;
}

#endif //WITH_DEV_AUTOMATION_TESTS