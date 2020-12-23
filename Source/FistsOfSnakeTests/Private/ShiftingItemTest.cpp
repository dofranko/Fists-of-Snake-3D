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

DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FShiftingItemCommand, FAutomationTestBase*, test);

bool FShiftingItemCommand::Update()
{
    if (!GEditor->IsPlayingSessionInEditor())//if not, everything would be made while the map is loading and the PIE is in progress.
    {
        return false;
    }

    UWorld* testWorld = GEditor->GetPIEWorldContext()->World();
    
	AFPSCharacter* Player = testWorld->SpawnActor<AFPSCharacter>(AFPSCharacter::StaticClass(), FVector(-180.0f, 30.0f, 120.0f), FRotator(0.f, 0.f, 0.f));
	AItem* Weapon = testWorld->SpawnActor<AWeapon>(AWeapon::StaticClass(), FVector(-180.0f, 30.0f, 120.0f), FRotator(0.f, 0.f, 0.f));
	AItem* Grenade = testWorld->SpawnActor<AGrenade>(AGrenade::StaticClass(), FVector(-180.0f, 30.0f, 120.0f), FRotator(0.f, 0.f, 0.f));
	AItem* Weapon2 = testWorld->SpawnActor<AWeapon>(AWeapon::StaticClass(), FVector(-180.0f, 30.0f, 120.0f), FRotator(0.f, 0.f, 0.f));
	TArray<UObject*> Array;
	EngineUtils::FindOrLoadAssetsByPath(TEXT("/Game/FPS_Weapon_Bundle/Weapons/Meshes/AR4"), Array, EngineUtils::ATL_Regular);
	USkeletalMesh* SkeletalMesh = Cast<USkeletalMesh>(Array[0]);
	Weapon->SkeletalMesh->SetSkeletalMesh(SkeletalMesh);
	Weapon2->SkeletalMesh->SetSkeletalMesh(SkeletalMesh);
	Grenade->SkeletalMesh->SetSkeletalMesh(SkeletalMesh);
	Player->MyInventory->AddItem(Weapon);
	Player->MyInventory->AddItem(Grenade);
	Player->MyInventory->AddItem(Weapon2);

	Player->ChooseItem(0);
	if (!Player->EquippedItem)
		test->AddError(TEXT("The position 0 is null"));
	Player->ThrowItem();
	if (Player->EquippedItem)
		test->AddError(TEXT("Player shouldn't have item after throwing it out"));
	if (Player->MyInventory->GetItem(0))
		test->AddError(TEXT("A throwed item shouldn't be in player's inventory"));
	if (Player->ManagerCamera)
		Player->ChooseItem(1);
	if (!Player->EquippedItem)
		test->AddError(TEXT("The position 1 is null"));
	Player->ChooseItem(2);
	if (!Player->EquippedItem)
		test->AddError(TEXT("The position 2 is null"));
	Player->ChooseItem(3);
	if (Player->EquippedItem)
		test->AddError(TEXT("The position 3 isn't null"));
	Player->ChooseItem(4);
	if (Player->EquippedItem)
		test->AddError(TEXT("The position 4 isn't null"));

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FShiftingItemTest, "ShiftingItemTest", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FShiftingItemTest::RunTest(const FString& Parameters)
{
    {
        ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(TEXT("/Game/Maps/FPSMapTest")));

        ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

        ADD_LATENT_AUTOMATION_COMMAND(FShiftingItemCommand(this));

        ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);

        ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(TEXT("/Game/Maps/MainMenuMAp")));
    }

    return true;
}

#endif //WITH_DEV_AUTOMATION_TESTS