// Fill out your copyright notice in the Description page of Project Settings.

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationEditorCommon.h"
#include <Runtime\Engine\Public\EngineUtils.h>
#include "FistsOfSnake/Grenade.h"
#include "FistsOfSnake/FPSCharacter.h"
#include <Editor/UnrealEd/Public/Editor.h>

/*
DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FEngineWaitLatentCommand, AFPSCharacter*, Player);

bool FEngineWaitLatentCommand::Update() 
{
	if (Player->GetHealth() == 0) 
		return false;
	return true;
}
*/

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


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGrenadeTest, "GrenadeTest", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FGrenadeTest::RunTest(const FString& Parameters)
{
	FAutomationEditorCommonUtils::LoadMap(TEXT("/Game/Maps/FPSMapTest"));
	UWorld* World = GetTestWorld();

	{
		AGrenade* Grenade = World->SpawnActor<AGrenade>(AGrenade::StaticClass(), FVector(-180.0f, 30.0f, 120.0f), FRotator(0.f, 0.f, 0.f));
		//ADD_LATENT_AUTOMATION_COMMAND(FEngineWaitLatentCommand(Player));

		int NumGrenades = Grenade->NumberOfGrenades;
		FActorSpawnParameters SpawnParams;
		for (int i = NumGrenades - 1; i >= 0; i--)
		{
			Grenade->Use(FVector(-180.f,30.f,120.f), FRotator(0.f, 0.f, 0.f), SpawnParams);
			if (Grenade->NumberOfGrenades != i)
				AddError(TEXT("Substraction of grenades doesn't work"));
			
		}
		if (Grenade->bAlive)
			AddError(TEXT("Grenade should disappear"));
		FAutomationEditorCommonUtils::LoadMap(TEXT("/Game/Maps/MainMenuMAp"));
	}

	return true;
}