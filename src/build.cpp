#include "build.hpp"
#include "build_system.hpp"
#include "fetch.hpp"

#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <string>
#include <thread>

namespace fs = std::filesystem;

static std::string shellQuote(const std::string& value)
{
    std::string result = "'";

    for (char character : value) {
        if (character == '\'') {
            result += "'\\''";
        } else {
            result += character;
        }
    }

    result += "'";

    return result;
}

static unsigned int buildJobs()
{
    unsigned int jobs = std::thread::hardware_concurrency();

    if (jobs == 0) {
        jobs = 1;
    }

    return jobs;
}

static fs::path findSourceDirectory(const fs::path& sourceRoot)
{
    for (const auto& entry : fs::directory_iterator(sourceRoot)) {
        if (entry.is_directory()) {
            return entry.path();
        }
    }

    throw std::runtime_error(
        "Could not find source directory in archive"
    );
}

static std::string archiveName(const fs::path& archivePath)
{
    std::string name = archivePath.filename().string();

    if (name.ends_with(".tar.gz")) {
        name.erase(name.size() - 7);
    }
    else if (name.ends_with(".tgz")) {
        name.erase(name.size() - 4);
    }
    else {
        throw std::runtime_error(
            "Only .tar.gz and .tgz archives are supported"
        );
    }

    return name;
}

void buildSource(const std::string& input)
{
    if (input.starts_with("http://") ||
        input.starts_with("https://")) {

        std::cout << "Fetching source...\n";

        const FetchResult result = fetchSource(input);

        std::cout << "Downloaded: "
                  << result.path
                  << '\n';

        std::cout << "SHA-256:    "
                  << result.hash
                  << '\n';

        buildSourceArchive(result.path);
        return;
    }

    buildSourceArchive(input);
}

void buildSourceArchive(const std::string& archive)
{
    const fs::path archivePath = fs::absolute(archive);

    if (!fs::exists(archivePath)) {
        throw std::runtime_error(
            "Archive not found: " + archivePath.string()
        );
    }

    const fs::path workRoot =
        fs::absolute("work");

    fs::create_directories(workRoot);

    const std::string name =
        archiveName(archivePath);

    const fs::path sourceRoot =
        workRoot / name;

    if (fs::exists(sourceRoot)) {
        fs::remove_all(sourceRoot);
    }

    fs::create_directories(sourceRoot);

    std::cout << "Extracting: "
              << archivePath.string()
              << '\n';

    const std::string extractCommand =
        "tar -xzf " +
        shellQuote(archivePath.string()) +
        " -C " +
        shellQuote(sourceRoot.string());

    if (std::system(extractCommand.c_str()) != 0) {
        fs::remove_all(sourceRoot);

        throw std::runtime_error(
            "Failed to extract archive"
        );
    }

    const fs::path sourceDir =
        findSourceDirectory(sourceRoot);

    std::cout << "Source: "
              << sourceDir.string()
              << '\n';

    const BuildSystem buildSystem =
        detectBuildSystem(sourceDir);

    std::cout << "Build system: "
              << buildSystemName(buildSystem)
              << '\n';

    const fs::path installDir =
        fs::absolute(sourceRoot / "install");

    fs::create_directories(installDir);

    const unsigned int jobs =
        buildJobs();

    /*
     * CMake
     */
    if (buildSystem == BuildSystem::CMake) {
        const fs::path buildDir =
            sourceRoot / "cmake-build";

        fs::create_directories(buildDir);

        std::cout << "Running CMake configure...\n";

        const std::string configureCommand =
            "cmake -S " +
            shellQuote(sourceDir.string()) +
            " -B " +
            shellQuote(buildDir.string()) +
            " -DCMAKE_BUILD_TYPE=Release"
            " -DCMAKE_INSTALL_PREFIX=" +
            shellQuote(installDir.string());

        if (std::system(configureCommand.c_str()) != 0) {
            throw std::runtime_error(
                "CMake configuration failed"
            );
        }

        std::cout << "Building with CMake...\n";

        const std::string buildCommand =
            "cmake --build " +
            shellQuote(buildDir.string()) +
            " --parallel " +
            std::to_string(jobs);

        if (std::system(buildCommand.c_str()) != 0) {
            throw std::runtime_error(
                "CMake build failed"
            );
        }

        std::cout << "Build completed successfully.\n";
        return;
    }

    /*
     * Autotools
     */
    if (buildSystem == BuildSystem::Autotools) {
        std::cout << "Running configure...\n";

        const std::string buildCommand =
            "cd " +
            shellQuote(sourceDir.string()) +
            " && ./configure --prefix=" +
            shellQuote(installDir.string()) +
            " && make -j" +
            std::to_string(jobs);

        if (std::system(buildCommand.c_str()) != 0) {
            throw std::runtime_error(
                "Autotools build failed"
            );
        }

        std::cout << "Build completed successfully.\n";
        return;
    }

    /*
     * Meson
     */
    if (buildSystem == BuildSystem::Meson) {
        const fs::path buildDir =
            sourceRoot / "meson-build";

        std::cout << "Running Meson configure...\n";

        const std::string setupCommand =
            "meson setup " +
            shellQuote(buildDir.string()) +
            " " +
            shellQuote(sourceDir.string()) +
            " --buildtype=release"
            " --prefix=" +
            shellQuote(installDir.string());

        if (std::system(setupCommand.c_str()) != 0) {
            throw std::runtime_error(
                "Meson configuration failed"
            );
        }

        std::cout << "Building with Meson...\n";

        const std::string buildCommand =
            "meson compile -C " +
            shellQuote(buildDir.string()) +
            " -j " +
            std::to_string(jobs);

        if (std::system(buildCommand.c_str()) != 0) {
            throw std::runtime_error(
                "Meson build failed"
            );
        }

        std::cout << "Build completed successfully.\n";
        return;
    }

    /*
     * Generic Make
     */
    if (buildSystem == BuildSystem::Make) {
        std::cout << "Building with Make...\n";

        const std::string buildCommand =
            "cd " +
            shellQuote(sourceDir.string()) +
            " && make -j" +
            std::to_string(jobs);

        if (std::system(buildCommand.c_str()) != 0) {
            throw std::runtime_error(
                "Make build failed"
            );
        }

        std::cout << "Build completed successfully.\n";
        return;
    }

    throw std::runtime_error(
        "Unsupported build system"
    );
}

void installSourceArchive(const std::string& archive)
{
    const fs::path archivePath =
        fs::absolute(archive);

    const std::string name =
        archiveName(archivePath);

    const fs::path sourceRoot =
        fs::absolute("work") / name;

    if (!fs::exists(sourceRoot)) {
        buildSourceArchive(archive);
    }

    const fs::path sourceDir =
        findSourceDirectory(sourceRoot);

    const BuildSystem buildSystem =
        detectBuildSystem(sourceDir);

    const fs::path installDir =
        sourceRoot / "install";

    if (buildSystem == BuildSystem::CMake) {
        const fs::path buildDir =
            sourceRoot / "cmake-build";

        std::cout << "Installing with CMake...\n";

        const std::string command =
            "cmake --install " +
            shellQuote(buildDir.string());

        if (std::system(command.c_str()) != 0) {
            throw std::runtime_error(
                "CMake install failed"
            );
        }
    }
    else if (buildSystem == BuildSystem::Autotools) {
        std::cout << "Installing with Make...\n";

        const std::string command =
            "cd " +
            shellQuote(sourceDir.string()) +
            " && make install";

        if (std::system(command.c_str()) != 0) {
            throw std::runtime_error(
                "Autotools install failed"
            );
        }
    }
    else if (buildSystem == BuildSystem::Meson) {
        const fs::path buildDir =
            sourceRoot / "meson-build";

        std::cout << "Installing with Meson...\n";

        const std::string command =
            "meson install -C " +
            shellQuote(buildDir.string());

        if (std::system(command.c_str()) != 0) {
            throw std::runtime_error(
                "Meson install failed"
            );
        }
    }
    else if (buildSystem == BuildSystem::Make) {
        throw std::runtime_error(
            "Automatic install for generic Make "
            "projects is not supported yet"
        );
    }
    else {
        throw std::runtime_error(
            "Unsupported build system for install"
        );
    }

    std::cout << "Installed to: "
              << installDir.string()
              << '\n';

    std::cout << "Install completed successfully.\n";
}