# Route Planning Project

This repo contains our implementation for the Route Planning Project, the first of Udacity's C++ Nanodegree, focused on the Foundations of the language.

<img src="map.png" width="600" height="450" />

Some of the challenges we faced were getting used to C++ syntax and mechanics, such as vector objects, or pointers usage and notation. The original repository can be found [here](https://github.com/udacity/CppND-Route-Planning-Project).

## Cloning

When cloning this project, be sure to use the `--recurse-submodules` flag. Using HTTPS:
```
git clone https://github.com/udacity/CppND-Route-Planning-Project.git --recurse-submodules
```
or with SSH:
```
git clone git@github.com:udacity/CppND-Route-Planning-Project.git --recurse-submodules
```

## Dependencies for Running Locally
* cmake >= 3.11.3
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 7.4.0
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same instructions as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* IO2D
  * Installation instructions for all operating systems can be found [here](https://github.com/cpp-io2d/P0267_RefImpl/blob/master/BUILDING.md)
  * The way the library is being called from `CMakeLists.txt` can also be found [here](https://github.com/cpp-io2d/P0267_RefImpl/blob/master/CONSUMING.md)
  * This library must be built in a place where CMake `find_package` will be able to find it

> ### Instalation Notes:
> This project was executed on Ubuntu 20.04.3 LTS Focal Fossa. In the following we describe the step-by-step procedure for installing IO2D:
> ```
> sudo apt update
> sudo apt install build-essential
> sudo apt install cmake
> sudo apt install libcairo2-dev
> sudo apt install libgraphicsmagick1-dev
> sudo apt install libpng-dev
> 
> git clone --recurse-submodules https://github.com/cpp-io2d/P0267_RefImpl
> cd P0267_RefImpl
> mkdir Debug
> cd Debug
> cmake --config Debug "-DCMAKE_BUILD_TYPE=Debug" ..
> cmake --build .
>
> sudo make install
> ```
> A lot of this is explained in the `P0267_RefImpl` repository documentation. However, the key point is to run `sudo make install` at the end.<br> 
> For other OS please refer to the following [issue](https://github.com/udacity/CppND-Route-Planning-Project/issues/1#issuecomment-520659977).<br> 
> Credit goes to the post made by [suljaxm](https://github.com/suljaxm).

## Compiling and Running

### Compiling
To compile the project, first, create a `build` directory and change to that directory:
```
mkdir build && cd build
```
From within the `build` directory, then run `cmake` and `make` as follows:
```
cmake ..
make
```
### Running
The executable will be placed in the `build` directory. From within `build`, you can run the project as follows:
```
./OSM_A_star_search
```
Or to specify a map file:
```
./OSM_A_star_search -f ../<your_osm_file.osm>
```

## Testing

The testing executable is also placed in the `build` directory. From within `build`, you can run the unit tests as follows:
```
./test
```

