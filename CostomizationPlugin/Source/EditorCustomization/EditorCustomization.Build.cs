using UnrealBuildTool;

public class EditorCustomization : ModuleRules
{
    public EditorCustomization(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "InputCore"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                // all detail panel editing needs Modules below
                "Slate",
                "SlateCore",
                "UnrealEd",
                "PropertyEditor"
            }
        );
    }
}