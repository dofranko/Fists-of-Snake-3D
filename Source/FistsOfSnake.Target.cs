// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class FistsOfSnakeTarget : TargetRules
{
	public FistsOfSnakeTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "FistsOfSnake" } );
		ExtraModuleNames.Add("FistsOfSnakeTests");
	}
}
