// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AnubisUnreal : ModuleRules
{
	public AnubisUnreal(ReadOnlyTargetRules Target) : base(Target)
	{
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
			"GameplayTasks"       
		});
	}
}
