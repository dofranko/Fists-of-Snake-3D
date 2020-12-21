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
/*
UWorld* GetTestWorld()
{
	const TIndirectArray<FWorldContext>& WorldContexts = GEngine->GetWorldContexts();
	for (const FWorldContext& Context : WorldContexts) {
		if (((Context.WorldType == EWorldType::PIE) || (Context.WorldType == EWorldType::Editor))
			&& (Context.World() != nullptr)) {
			return Context.World();
		}
	}
	return nullptr;
}
*/
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FShiftingItemTest, "ShiftingItemTest", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FShiftingItemTest::RunTest(const FString& Parameters)
{
	FAutomationEditorCommonUtils::LoadMap(TEXT("/Game/Maps/FPSMapTest"));
	UWorld* World = nullptr;
	const TIndirectArray<FWorldContext>& WorldContexts = GEngine->GetWorldContexts();
	for (const FWorldContext& Context : WorldContexts) {
		if (((Context.WorldType == EWorldType::PIE) || (Context.WorldType == EWorldType::Editor))
			&& (Context.World() != nullptr)) {
			World = Context.World();
		}
	}

	{
		AFPSCharacter* Player = World->SpawnActor<AFPSCharacter>(AFPSCharacter::StaticClass(), FVector(-180.0f, 30.0f, 120.0f), FRotator(0.f, 0.f, 0.f));
		Player->World = World;
		Player->Initialize();
		AItem* Weapon = World->SpawnActor<AWeapon>(AWeapon::StaticClass(), FVector(-180.0f, 30.0f, 120.0f), FRotator(0.f, 0.f, 0.f));
		AItem* Grenade = World->SpawnActor<AGrenade>(AGrenade::StaticClass(), FVector(-180.0f, 30.0f, 120.0f), FRotator(0.f, 0.f, 0.f));
		AItem* Weapon2 = World->SpawnActor<AWeapon>(AWeapon::StaticClass(), FVector(-180.0f, 30.0f, 120.0f), FRotator(0.f, 0.f, 0.f));
		TArray<UObject*> Array;
		EngineUtils::FindOrLoadAssetsByPath(TEXT("/Game/FPS_Weapon_Bundle/Weapons/Meshes/AR4"), Array, EngineUtils::ATL_Regular);
		USkeletalMesh* SkeletalMesh = Cast<USkeletalMesh>(Array[0]);
		Weapon->SkeletalMesh->SetSkeletalMesh(SkeletalMesh);
		Weapon2->SkeletalMesh->SetSkeletalMesh(SkeletalMesh);
		Grenade->SkeletalMesh->SetSkeletalMesh(SkeletalMesh);
		Player->MyInventory->AddItem(Weapon);
		Player->MyInventory->AddItem(Grenade);
		Player->MyInventory->AddItem(Weapon2);

		if (!Cast<AWeapon>(Player->EquippedItem))
			AddError(TEXT("At the index 0 should be the weapon"));
		//Player->ThrowItem();
		if (Player->EquippedItem)
			AddError(TEXT("Player shouldn't have item after throwing it out"));
		if (Player->MyInventory->GetItem(0))
			AddError(TEXT("A throwed item shouldn't be in player's inventory"));
		//Player->ChooseItem(0);
		if (Player->EquippedItem)
			AddError(TEXT("The position 0 isn't null"));
		if(Player->ManagerCamera)
			Player->ChooseItem(1);
		if (!Player->EquippedItem)
			AddError(TEXT("The position 1 is null"));
		//Player->ChooseItem(2);
		if (!Player->EquippedItem)
			AddError(TEXT("The position 2 is null"));

	}

	FAutomationEditorCommonUtils::LoadMap(TEXT("/Game/Maps/MainMenuMAp"));

	return true;
}