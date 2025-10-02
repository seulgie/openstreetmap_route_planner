# OpenStreetMap Route Planner

This repo contains a C++ project that implements a **route planning application** using real map data from the [OpenStreetMap](https://www.openstreetmap.org/). 
This application reads map data, calculates the shortest path between two points 
using the **A* search algorithm**, and visually renders the route on a 2D map using the
**IO2D graphics library**.
This project demonstrates:
- C++ practice: including classes, pointers, references, and STL containers.
- Algorithm implementation: A* pathfinding with heuristics.
- Practical application: Working with real-world map data (OpenStreetMap).
- Unit testing: Ensuring correctness with Google Test.

<img src="map.png" width="600" height="450" />

---

## Project Overview

The goal of this project is to simulate a real-world route planning system, 
similar to the functionality found in mapping applications like Google Maps.
This project focuses on:

- Parsing **OpenStreetMap XML (.osm) data**.
- Building a **graph model** of nodes and edges (RouteModel).
- Implementing the **A* search algorithm** to find the shortest path.
- Rendering the map and the calculated route with **IO2D**.

---

openstreetmap_route_planner/
├── cmake/           # CMake configuration files (do not modify)
├── src/             # Source code (main.cpp, route_model.cpp, route_planner.cpp, render.cpp)
├── test/            # Unit tests using Google Test framework
├── thirdparty/      # Third-party libraries (IO2D)
├── build/           # Build output (created after building)
├── map.osm          # Example OpenStreetMap data
└── README.md



---

## Cloning

The starter codes are in 'https://github.com/udacity/CppND-Route-Planning-Project.git'.
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
  * This library must be built in a place where CMake `find_package` will be able to find it

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
---

## Key Features
- A Search Algorithm: Finds the shortest path efficiently.
- RouteModel: Converts OSM data into nodes and edges for pathfinding.
- Visual Rendering: IO2D library displays the map and calculated routes.
- User Input: Start and end coordinates can be specified at runtime.
- Modular Design: Easily extendable and testable code structure.





