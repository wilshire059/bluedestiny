// SLF_5_7.Build.cs
using UnrealBuildTool;
using System.IO;

public class SLF_5_7 : ModuleRules
{
	public SLF_5_7(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		// Include paths for the Converted folder (incremental conversion)
		// ManualConversion folder is moved to BlueDestiny\ManualConversion_Staging (outside Source)
		PublicIncludePaths.AddRange(new string[] {
			Path.Combine(ModuleDirectory, "Converted"),
			Path.Combine(ModuleDirectory, "Converted", "Enums"),
			Path.Combine(ModuleDirectory, "Converted", "Structs"),
			Path.Combine(ModuleDirectory, "Converted", "Interfaces"),
			Path.Combine(ModuleDirectory, "Converted", "DataAssets"),
			Path.Combine(ModuleDirectory, "Converted", "Components"),
			Path.Combine(ModuleDirectory, "Converted", "Classes"),
			Path.Combine(ModuleDirectory, "Converted", "Animation"),
			Path.Combine(ModuleDirectory, "Converted", "AI"),
			Path.Combine(ModuleDirectory, "Converted", "CameraShakes"),
			Path.Combine(ModuleDirectory, "Converted", "Libraries")
		});
	
		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"UMG",
			"Slate",
			"SlateCore",
			"GameplayTags",
			"GameplayTasks",
			"AIModule",
			"NavigationSystem",
			"Niagara",
			"GeometryCollectionEngine",
			"ChaosSolverEngine",
			"PhysicsCore",
			"EngineCameras",
			"StructUtils",
			"LevelSequence"
		});

		// Editor-only modules (Blutility for Editor Utility Widgets)
		if (Target.bBuildEditor)
		{
			PrivateDependencyModuleNames.AddRange(new string[] {
				"Blutility",
				"UnrealEd",
				"UMGEditor"
			});
		}
	}
}