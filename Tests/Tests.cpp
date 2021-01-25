
#include "pch.h"
#include "CppUnitTest.h"
#include "../Source/FistsOfSnake/Inventory.h"
#include "../Source/FistsOfSnake/Item.h"
#include "../Source/FistsOfSnake/Weapon.h"
#include "../Source/FistsOfSnake/Grenade.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(Tests)
	{
	private:
		Inventory *mock;

	public:
		
		TEST_METHOD(InventoryTest)
		{
			
			AItem weapon1();
			//AItem* Grenade = NewObject<AGrenade>();
			//AItem* Weapon2 = NewObject<AWeapon>();
			Inventory->AddItem(AItem);
			//MyInventory->AddItem(Grenade);
			//MyInventory->AddItem(Weapon2);
			// Check if index of array works
			//AGrenade* Wep = Cast<AGrenade>(MyInventory->GetItem(1));
			//if (!Wep)
			//	AddError("At position 1 should be a grenade");
			//Inventory.RemoveItem(1);
			// Check if after deleting item will be null position, array not to resize
			//if (MyInventory->GetItem(1))
			//	AddError("Array was resized");
			//MyInventory->AddItem(Grenade);
			// Check if after adding an item it will be located at the first null position
			//Wep = Cast<AGrenade>(MyInventory->GetItem(1));
			//if (!Wep)
			//	AddError("It should add an item on the first null position");
		}
	};
}
