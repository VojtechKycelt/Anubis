// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AnubisUnreal : ModuleRules
{
	public AnubisUnreal(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] { "RigLogicLib" });
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput",
			//GAS dependencies
			"GameplayAbilities",
			"GameplayTags",       
			"GameplayTasks",
			//AI
			"AIModule",
			//UI,
			"UMG",
		});
		
		PublicIncludePaths.Add("AnubisUnreal");
	}
}
