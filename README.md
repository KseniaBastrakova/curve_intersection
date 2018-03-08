# curve_intersector

## About
An open source C++ library for curves in 2D. Provides:
  - Representation of parametric curves
  - Intersection algorithms
  - Serialization

The library supports the following types of curves:
  - Line segment
  - Circle
  - Ellipse
  - Bézier curves

## How to build

The code is cross-platform and can be built using cmake with the 
provided CMakeLists.txt file. There are no external dependencies.

The compiled library to lib directory. 
The compiled unit tests are put to bin directory and run at the end of each build. 

## How to use

Add include subdirectory to additional include paths. 
Add lib to additional static library paths, link with the 
static library curve_intersection.a or curve_intersection.lib depending on your system. 