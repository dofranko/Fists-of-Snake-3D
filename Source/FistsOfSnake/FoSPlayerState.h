// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "FoSPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class FISTSOFSNAKE_API AFoSPlayerState : public APlayerState
{
	GENERATED_BODY()


public:
	AFoSPlayerState();

	/** Property replication */
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "Stats")
	int deaths;

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "Stats")
	int kills;
};
