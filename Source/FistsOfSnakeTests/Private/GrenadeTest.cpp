// Fill out your copyright notice in the Description page of Project Settings.

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationEditorCommon.h"
#include <Runtime\Engine\Public\EngineUtils.h>
#include "FistsOfSnake/Grenade.h"
#include "FistsOfSnake/FPSCharacter.h"
#include <Editor/UnrealEd/Public/Editor.h>

#if WITH_DEV_AUTOMATION_TESTS

DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FGrenadeCommand, FAutomationTestBase*, test);

bool FGrenadeCommand::Update()
{
    if (!GEditor->IsPlayingSessionInEditor())//if not, everything would be made while the map is loading and the PIE is in progress.
    {
        return false;
    }

    UWorld* testWorld = GEditor->GetPIEWorldContext()->World();
    
	AFPSCharacter* Player = testWorld->SpawnActor<AFPSCharacter>(AFPSCharacter::StaticClass(), FVector(-180.0f, 30.0f, 120.0f), FRotator(0.f, 0.f, 0.f));
	AGrenade* Grenade = testWorld->SpawnActor<AGrenade>(AGrenade::StaticClass(), FVector(-180.0f, 30.0f, 120.0f), FRotator(0.f, 0.f, 0.f));

	int NumGrenades = Grenade->NumberOfGrenades;
	for (int i = NumGrenades - 1; i >= 0; i--)
	{
		Grenade->Use(FVector(-180.f,30.f,120.f), FRotator(0.f, 0.f, 0.f));
		if (Grenade->NumberOfGrenades != i)
			test->AddError(TEXT("Substraction of grenades doesn't work"));
			
		}
		if (Grenade->bAlive)
			test->AddError(TEXT("Grenade should disappear"));

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGrenadeTest, "GrenadeTest", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FGrenadeTest::RunTest(const FString& Parameters)
{
    {

        ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(TEXT("/Game/Maps/FPSMapTest")));

        ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

        ADD_LATENT_AUTOMATION_COMMAND(FGrenadeCommand(this));

        ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);

        ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(TEXT("/Game/Maps/MainMenuMAp")));
    }

    return true;
}

#endif //WITH_DEV_AUTOMATION_TESTS