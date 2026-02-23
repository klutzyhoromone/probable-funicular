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
  xorg.libX11
  xorg.libXcursor
  freeglut
  xorg.libXi
  xorg.libXinerama
  xorg.libXrandr
  glfw
  xorg.libxcb
  freetype
];

        nativeBuildInputs = with pkgs;[
          cmake
	        xorg.libX11.dev
          xorg.libXcursor
          xorg.libXi
          glew
          xorg.libXinerama
          xorg.libXrandr
          SDL2    
          libGLU
          pkg-config
	  ];

        # Provide environment variables useful for build
        shellHook = ''

          export LD_LIBRARY_PATH=${pkgs.lib.makeLibraryPath (with pkgs; [
            libGL 
            glew
            xorg.libX11
            SDL2
            libGLU
            xorg.libXcursor
            xorg.libXi
            xorg.libXinerama
            xorg.libXrandr
            glfw
	          freeglut
            openal
            alsa-lib
            pulseaudio
            pipewire
          ])}:$LD_LIBRARY_PATH

          # For compile-time search
          export PKG_CONFIG_PATH=${pkgs.lib.makeLibraryPath (with pkgs; [
            xorg.libX11
            SDL2
            glew
            libGLU
            xorg.libXcursor
            xorg.libXi
            xorg.libXinerama
            xorg.libXrandr
            glfw
            freeglut
          ])}/lib/pkgconfig:$PKG_CONFIG_PATH
        '';
      };
    };
}
