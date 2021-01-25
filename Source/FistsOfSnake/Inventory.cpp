// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"
#include "Item.h"
#include "Weapon.h"

Inventory::Inventory()
{
	this->Size = 5;
	this->ArrayOfItems.Init(nullptr, this->Size);
}

bool Inventory::AddItem(AItem* Item)
{
	for (int Index = 0; Index != this->Size; ++Index)
	{
		if (!this->ArrayOfItems[Index])
		{
			this->ArrayOfItems[Index] = Item;
			return true;
		}
	}
	return false;
}


void Inventory::RemoveItem(int Index)
{
	this->ArrayOfItems[Index] = nullptr;
}

AItem* Inventory::GetItem(int Index)
{
	return this->ArrayOfItems[Index];
}

UTexture2D* Inventory::GetItemIcon(int Index)
{
	if (this->ArrayOfItems[Index])
		return this->ArrayOfItems[Index]->ItemIcon;
	return nullptr;
}

void Inventory::DestroyItems()
{
	for (int Index = 0; Index != this->Size; ++Index)
	{
		if (this->ArrayOfItems[Index])
		{
			this->ArrayOfItems[Index]->Destroy();
			this->ArrayOfItems[Index] = nullptr;
		}
	}
}

Inventory::~Inventory()
{
}