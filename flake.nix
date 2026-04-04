{
  description = "Raylib environment";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs, ... }:
    let
      system = "x86_64-linux";
      pkgs = import nixpkgs { inherit system; };
    in {
      devShells.${system}.default = pkgs.mkShell {
        # Use buildInputs (for runtime linking) and nativeBuildInputs (for build tools)
buildInputs = with pkgs; [
  libGL
  glew
  openal
  alsa-lib
  pulseaudio
  pipewire
  SDL2
  libGLU
  libxkbcommon
  libX11
  libXcursor
  freeglut
  libXi
  libXinerama
  libXrandr
  glfw
  libxcb
  freetype
];

        nativeBuildInputs = with pkgs;[
          cmake
	        libX11.dev
          libXcursor
          libXi
          glew
          libXinerama
          libXrandr
          SDL2    
          libGLU
          pkg-config
	  ];

        # Provide environment variables useful for build
        shellHook = ''

          export LD_LIBRARY_PATH=${pkgs.lib.makeLibraryPath (with pkgs; [
            libGL 
            glew
            libX11
            SDL2
            libGLU
            libXcursor
            libXi
            libXinerama
            libXrandr
            glfw
	          freeglut
            openal
            alsa-lib
            pulseaudio
            pipewire
          ])}:$LD_LIBRARY_PATH

          # For compile-time search
          export PKG_CONFIG_PATH=${pkgs.lib.makeLibraryPath (with pkgs; [
            libX11
            SDL2
            glew
            libGLU
            libXcursor
            libXi
            libXinerama
            libXrandr
            glfw
            freeglut
          ])}/lib/pkgconfig:$PKG_CONFIG_PATH
        '';
      };
    };
}
