// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FistsOfSnakeGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class FISTSOFSNAKE_API AFistsOfSnakeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	virtual void StartPlay() override;
};

