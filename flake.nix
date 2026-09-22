{
  description = "nix-src - source-based build tool for Nix";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs }:
    let
      system = "x86_64-linux";
      pkgs = import nixpkgs { inherit system; };
    in {
      devShells.${system}.default = pkgs.mkShell {
        packages = with pkgs; [
          gcc
          cmake
          gdb
          openssl
          curl.dev
          pkg-config
          gnumake
          meson
        ];

        shellHook = ''
          echo "nix-src development environment"
          echo "GCC: $(g++ --version | head -n1)"
          echo "CMake: $(cmake --version | head -n1)"
        '';
      };
    };
}
