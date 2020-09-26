# Maze Generator
An OpenGL application built in C++ that generates a 3D map using a 2D defined grid.
Requires GLFW and glad libraries for platform specific functionality and system interaction.

## Input
As shown in grid.txt idea is to have a arbitrarily defined grid using
* '0' for an empty space
* '*' for a closed space
* 'c' for the initial camera position

Example:
```
00000000000
00000000000
00*******00
00***c***00
00*******00
0000***0000
00000000000
00000000000
```

## Usage
Download the source libraries for GLFW GLAD and GLM and edit CMakeLists.txt LIB_DIR var to point to a directory
that stores all of the libraries sources.
Run the following in thee root directory:
```
mkdir build
cd build
cmake ..
make
mv MazeGenerator ../
```
After moving the built executable to root run the executable in root to access shader files and textures.
**Only Run Executable in Root Directory**
```
./MazeGenerator
```
## Render
Creates a 3D space for simple game prototyping
![Render Demo](/render.gif)
