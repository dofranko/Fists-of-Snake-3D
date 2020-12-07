// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

//Forward include
class AItem;
class AWeapon;

class FISTSOFSNAKE_API Inventory
{
public:

	Inventory();

	uint8 capacity = 20;

	TArray<AItem*> ArrayOfItems;

	bool AddItem(AItem* Item);

	AItem* GetItem(uint8 index);

	AItem* RemoveItem(uint8 index);

	AItem* GetItemToThrow();

	AWeapon* GetWeapon();

	~Inventory();
};