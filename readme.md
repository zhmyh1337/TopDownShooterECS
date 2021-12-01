# ECS Top-down Shooter (still in progress)
## Description
This is a small game I'm making as a part of my computer graphics course.
## Directories
### Source codes
Source codes are in `Projects/` directory:
* `Common/` subdirectory contains engine source code, ECS implementation and libraries (most of the code in this directory was not written by me, I only modified some files).
* `ECSCodeGen/` subdirectory contains code generation for the ECS (not my code).
* `TopDownShooter/` subdirectory contains the sources of the game, including textures and shaders. My code almost doesn't use OOP because the ECS implementation doesn't seem to fully support it.
### Binaries
Binaries are in `Builds/win/`.
## Building
To build the thing you need an installed [LLVM-12.0.0-win64.exe](https://github.com/llvm/llvm-project/releases/tag/llvmorg-12.0.0), [Ninja](https://github.com/ninja-build/ninja) and CMake. The locations of all binaries must be in the PATH env var. Use `build_script.bat` to build for win or `build_script.sh` to build for linux. Or use VS code with [plugin 1](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) and [plugin 2](https://marketplace.visualstudio.com/items?itemName=AlexandrShcherbakov.launchoption
) to build with Ctrl+Shift+B and run with F5.
## Demo
<img src="demo.gif?raw=true">