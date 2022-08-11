//  hidparse.lib


using System;
using System.IO;
using UnrealBuildTool;

public class FPV : ModuleRules
{
	public FPV(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        // Add any import libraries or static libraries
        PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib", "hid.lib"));


    }
}
