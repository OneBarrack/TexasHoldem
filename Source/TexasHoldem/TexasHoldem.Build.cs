// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TexasHoldem : ModuleRules
{
	public TexasHoldem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"HeadMountedDisplay", 
			"UMG"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { 
			"Slate", 
			"SlateCore" 
		});

		PublicIncludePaths.AddRange(new string[] {
			"TexasHoldem"
		});
	}
}
