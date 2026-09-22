#include "build_system.hpp"

#include <filesystem>

namespace fs = std::filesystem;

BuildSystem detectBuildSystem(const fs::path& sourceDir)
{
    /*
     * CMake
     */
    if (fs::exists(sourceDir / "CMakeLists.txt")) {
        return BuildSystem::CMake;
    }

    /*
     * Meson
     */
    if (fs::exists(sourceDir / "meson.build")) {
        return BuildSystem::Meson;
    }

    /*
     * Autotools
     */
    if (fs::exists(sourceDir / "configure")) {
        return BuildSystem::Autotools;
    }

    /*
     * Generic Make
     */
    if (fs::exists(sourceDir / "Makefile") ||
        fs::exists(sourceDir / "makefile") ||
        fs::exists(sourceDir / "GNUmakefile")) {
        return BuildSystem::Make;
    }

    return BuildSystem::Unknown;
}

const char* buildSystemName(BuildSystem system)
{
    switch (system) {
        case BuildSystem::CMake:
            return "CMake";

        case BuildSystem::Autotools:
            return "Autotools";

        case BuildSystem::Meson:
            return "Meson";

        case BuildSystem::Make:
            return "Make";

        case BuildSystem::Unknown:
            return "Unknown";
    }

    return "Unknown";
}