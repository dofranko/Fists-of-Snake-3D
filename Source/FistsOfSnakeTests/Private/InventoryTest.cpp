// Fill out your copyright notice in the Description page of Project Settings.

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include <Runtime\Engine\Public\EngineUtils.h>
#include "FistsOfSnake/Inventory.h"
#include "FistsOfSnake/Item.h"
#include "FistsOfSnake/Weapon.h"
#include "FistsOfSnake/Grenade.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FInventoryTest, "InventoryTest", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FInventoryTest::RunTest(const FString& Parameters)
{

	{
		Inventory* MyInventory = new Inventory();
		AItem* Weapon = NewObject<AWeapon>();
		AItem* Grenade = NewObject<AGrenade>();
		AItem* Weapon2 = NewObject<AWeapon>();
		MyInventory->AddItem(Weapon);
		MyInventory->AddItem(Grenade);
		MyInventory->AddItem(Weapon2);
		// Check if index of array works
		AGrenade* Wep = Cast<AGrenade>(MyInventory->GetItem(1));
		if (!Wep)
			AddError("At position 1 should be a grenade");
		MyInventory->RemoveItem(1);
		// Check if after deleting item will be null position, array not to resize
		if (MyInventory->GetItem(1))
			AddError("Array was resized");
		MyInventory->AddItem(Grenade);
		// Check if after adding an item it will be located at the first null position
		Wep = Cast<AGrenade>(MyInventory->GetItem(1));
		if (!Wep)
			AddError("It should add an item on the first null position");
	}

	return true;
}