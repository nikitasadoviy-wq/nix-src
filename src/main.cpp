#include "build.hpp"
#include "cpu.hpp"
#include "fetch.hpp"
#include "hash.hpp"

#include <exception>
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    if (argc == 1) {
        std::cout << "nix-src 0.1.0\n";
        std::cout << "Source-based build system for Nix\n";
        std::cout << "Use 'nix-src --help' for help.\n";
        return 0;
    }

    const std::string argument = argv[1];

    if (argument == "info") {
        const CpuInfo cpu = detectCpu();

        std::cout << "CPU: " << cpu.model << '\n';
        std::cout << "Vendor: " << cpu.vendor << '\n';
        std::cout << "Architecture: " << cpu.architecture << '\n';
        std::cout << "Profile: " << cpu.profile << '\n';

        return 0;
    }

    if (argument == "fetch") {
        if (argc < 3) {
            std::cerr << "Usage: nix-src fetch <url>\n";
            return 1;
        }

        try {
            const FetchResult result = fetchSource(argv[2]);

            std::cout << "Downloaded: " << result.path << '\n';
            std::cout << "SHA-256:    " << result.hash << '\n';
        }
        catch (const std::exception& error) {
            std::cerr << "Error: " << error.what() << '\n';
            return 1;
        }

        return 0;
    }

    if (argument == "build") {
        if (argc < 3) {
            std::cerr << "Usage: nix-src build <archive>\n";
            return 1;
        }

        try {
            buildSource(argv[2]);
        }
        catch (const std::exception& error) {
            std::cerr << "Error: " << error.what() << '\n';
            return 1;
        }

        return 0;
    }

    if (argument == "install") {
    if (argc < 3) {
        std::cerr << "Usage: nix-src install <archive>\n";
        return 1;
    }

    try {
        installSourceArchive(argv[2]);
    }
    catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }

    return 0;
}

    if (argument == "hash") {
        if (argc < 3) {
            std::cerr << "Usage: nix-src hash <file> [--check <sha256>]\n";
            return 1;
        }

        try {
            const std::string path = argv[2];
            const std::string actual = sha256File(path);

            if (argc == 5 && std::string(argv[3]) == "--check") {
                const std::string expected = argv[4];

                if (verifySha256(path, expected)) {
                    std::cout << "Hash verified.\n";
                    return 0;
                }

                std::cout << "Hash mismatch!\n";
                std::cout << "Expected: " << expected << '\n';
                std::cout << "Actual:   " << actual << '\n';

                return 1;
            }

            std::cout << actual << '\n';
        }
        catch (const std::exception& error) {
            std::cerr << "Error: " << error.what() << '\n';
            return 1;
        }

        return 0;
    }

    if (argument == "--version" || argument == "-V") {
        std::cout << "nix-src 0.1.0\n";
        return 0;
    }

    if (argument == "--help" || argument == "-h") {
        std::cout << "Usage: nix-src <command> [options]\n\n";
        std::cout << "Commands:\n";
        std::cout << "  info       Show system information\n";
        std::cout << "  hash       Calculate SHA-256 hash\n";
        std::cout << "  fetch      Fetch package source\n";
        std::cout << "  build      Fetch and build a source package\n";
        std::cout << "  generate   Generate a Nix derivation\n";
        std::cout << "  clean      Clean build files\n\n";
        std::cout << "Options:\n";
        std::cout << "  -h, --help       Show this help\n";
        std::cout << "  -V, --version    Show version\n";
        std::cout << "  install    Install a built package\n";

        return 0;
    }

    std::cout << "Unknown command: " << argument << '\n';
    std::cout << "Use 'nix-src --help' for help.\n";

    return 1;
}