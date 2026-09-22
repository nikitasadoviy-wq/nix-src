#pragma once

#include <filesystem>

enum class BuildSystem {
    CMake,
    Autotools,
    Meson,
    Make,
    Unknown
};

BuildSystem detectBuildSystem(
    const std::filesystem::path& sourceDir
);

const char* buildSystemName(BuildSystem system);