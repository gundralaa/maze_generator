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
## Render
Creates a 3D space for simple game prototyping
![Render Demo](/render.gif)
