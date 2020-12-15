// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

//Forward include
class AItem;

class FISTSOFSNAKE_API Inventory
{
public:

	Inventory();

	int Size;

	TArray<AItem*> ArrayOfItems;

	bool AddItem(AItem* Item);

	void RemoveItem(int Index);

	AItem* GetItem(int Index);

	UTexture2D* GetItemIcon(int Index);

	void DestroyItems();

	~Inventory();
};