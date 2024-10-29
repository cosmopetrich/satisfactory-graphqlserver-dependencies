/*
 * From https://docs.ficsit.app/satisfactory-modding/latest/Development/Cpp/thirdparty.html
 *
 * The include/lib files are not stored in git and are copied into place via a script.
 * Check CONTRIBUTING.md for more information. 
 */

using System.IO;
using UnrealBuildTool;

public class GQLServerDeps : ModuleRules {
    public GQLServerDeps(ReadOnlyTargetRules Target) : base(Target) {
        Type = ModuleType.External;
        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "include"));

        var PlatformName = Target.Platform.ToString();

        // Enable one OR the other of the following
        var LibFolder = Path.Combine(ModuleDirectory, "lib", PlatformName);
        // var LibFolder = Path.Combine(ModuleDirectory, "debug", PlatformName);

        if (Target.Platform == UnrealTargetPlatform.Win64) {
            PublicAdditionalLibraries.AddRange(Directory.EnumerateFiles(LibFolder, "*.lib"));
        }
        else if (Target.Platform == UnrealTargetPlatform.Linux) {
            PublicAdditionalLibraries.AddRange(Directory.EnumerateFiles(LibFolder, "*.a"));
        }
    }
}


