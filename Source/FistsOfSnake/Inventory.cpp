// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"
#include "Item.h"
#include "Weapon.h"

Inventory::Inventory()
{
	this->capacity = 20;
}

bool Inventory::AddItem(AItem* Item)
{
	if (this->capacity > this->ArrayOfItems.Num())
	{
		this->ArrayOfItems.Add(Item);
		return true;
	}
	return false;
}

AItem* Inventory::GetItem(uint8 index)
{
	return this->ArrayOfItems[index];
}

AItem* Inventory::RemoveItem(uint8 index)
{

	return this->ArrayOfItems[index];
}

AItem* Inventory::GetItemToThrow()
{
	if(this->ArrayOfItems.Num() != 0)
		return this->ArrayOfItems.Pop();
	return nullptr;
}

AWeapon* Inventory::GetWeapon()
{
	for (auto& CurrentItem : this->ArrayOfItems)
	{
		AWeapon* tmp = Cast<AWeapon>(CurrentItem);
		if (tmp) {
			this->ArrayOfItems.RemoveSingle(CurrentItem);
			return tmp;
		}
	}
	return nullptr;
}

Inventory::~Inventory()
{
}