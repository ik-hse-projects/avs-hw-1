let
  pkgs = import <nixpkgs> {};
in pkgs.mkShell {
  buildInputs = with pkgs; [
    cmake
    llvmPackages_12.clang
  ];
}
