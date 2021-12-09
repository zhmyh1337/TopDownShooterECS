# ECS Top-down Shooter (still in progress)
## Description
This is a small game I'm making as a part of my computer graphics course.
## Some of the features
* Infinite (but empty 🙂) world.
* Camera zooming.
* Dynamic difficulty (exponential distribution dependent on kill count).
* Enemies always spawn outside of the camera.
* Enemies vary in size, which affects health and damage.
* Dead enemies leave behind blood particles that disappear over time.
* Health, health bar and simple shader effect of taking damage.
* Dynamic fog (Perlin noise).
* Spatial sound effects.
* Primitive shadows.
## Peculiarities
This was the first time I used an ECS framework, and the framework provided (I didn't write it) lacked some essential, in my opinion, ECS functionality. So my code, even though it used ECS stuff, can hardly be considered as such, it's more like procedural. Plus, it was written rather hastily, so there may be some messy places.
## Directories
### Source codes
Source codes are in `Projects/` directory:
* `Common/` subdirectory contains engine source code, ECS implementation and libraries (most of the code in this directory was not written by me, I only modified some files).
* `ECSCodeGen/` subdirectory contains code generation for the ECS (not my code).
* `TopDownShooter/` subdirectory contains source codes for the game itself.
### Binaries
Binaries are in `Builds/TopDownShooter/`. Including all the resources.
## Building
To build the thing you need an installed [LLVM-12.0.0-win64.exe](https://github.com/llvm/llvm-project/releases/tag/llvmorg-12.0.0), [Ninja](https://github.com/ninja-build/ninja) and CMake. The locations of all the binaries must be in PATH environment variable. Use `build_script.bat` to build for win or `build_script.sh` to build for linux (with the first parameter `TopDownShooter` and the second either `dbg` or `rel`). Or use VS code with [plugin 1](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) and [plugin 2](https://marketplace.visualstudio.com/items?itemName=AlexandrShcherbakov.launchoption
) to build with Ctrl+Shift+B and run with F5.
## Demo
<img src="demo.gif?raw=true">
