# nix-src

A source-based build tool for Nix, inspired by the workflow of Void Linux `xbps-src`.

`nix-src` fetches source archives, verifies SHA-256 hashes, detects common build systems, and builds software from source.

## Features

- CPU and architecture detection
- SHA-256 hashing and verification
- Source fetching from HTTP/HTTPS
- Automatic build-system detection
- CMake support
- Autotools support
- Meson support
- Make support
- Parallel builds using available CPU threads
- Local source and build workspaces

## Supported build systems

`nix-src` currently detects build systems in this order:

1. CMake
2. Meson
3. Autotools
4. Make

## Commands

```text
nix-src --version
nix-src --help
nix-src info

nix-src fetch <url>

nix-src build <archive>
nix-src build <url>

nix-src install <archive>

nix-src hash <file>
nix-src hash <file> --check <sha256>
Examples

Fetch a source archive:

nix-src fetch https://ftp.gnu.org/gnu/hello/hello-2.12.1.tar.gz

Build a downloaded archive:

nix-src build sources/hello-2.12.1.tar.gz

Build directly from a URL:

nix-src build https://ftp.gnu.org/gnu/hello/hello-2.12.1.tar.gz

Calculate a SHA-256 hash:

nix-src hash flake.nix

Verify a SHA-256 hash:

nix-src hash flake.nix --check <sha256>

Show CPU and architecture information:

nix-src info
Building nix-src

Requirements:

C++23 compiler
CMake
OpenSSL
libcurl

Build with CMake:

cmake -B build
cmake --build build

The resulting binary is:

build/nix-src
Project layout
nix-src/
├── include/     # Header files
├── src/         # Source code
├── build/       # Generated build directory
├── sources/     # Downloaded source archives
├── work/        # Extracted and built sources
├── CMakeLists.txt
├── flake.nix
├── flake.lock
├── README.md
└── LICENSE

build/, sources/, and work/ are generated directories and are ignored by Git.

Status

nix-src is an early-stage project.

The current focus is building a solid source-build engine that can later integrate more deeply with the Nix package model.

License

This project is licensed under the GNU General Public License version 3.0.
See LICENSE for the full license text.
