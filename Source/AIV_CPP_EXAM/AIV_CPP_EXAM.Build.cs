// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AIV_CPP_EXAM : ModuleRules
{
	public AIV_CPP_EXAM(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
	}
}
