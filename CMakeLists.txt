cmake_minimum_required(VERSION 3.10)
project(heckers-engine)

set(CMAKE_CXX_STANDARD 11)


set(CMAKE_CXX_STANDARD_LIBRARIES "-lallegro_primitives -lallegro")
add_executable(Checkers-engine src/main.cpp src/PositionRater.cpp include/PositionRater.h include/Color.h src/MoveFinder.cpp include/MoveFinder.h src/PositionDrawer.cpp include/PositionDrawer.h)