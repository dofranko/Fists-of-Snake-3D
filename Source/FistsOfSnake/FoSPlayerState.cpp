// Fill out your copyright notice in the Description page of Project Settings.


#include "FoSPlayerState.h"
#include "Net/UnrealNetwork.h"

AFoSPlayerState::AFoSPlayerState() {
	deaths = 0;
	kills = 0;
}

void AFoSPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//Replicate current health.
	DOREPLIFETIME(AFoSPlayerState, deaths);
	DOREPLIFETIME(AFoSPlayerState, kills);
}