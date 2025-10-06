#CMake is not mandatory for your solution, this is provided simply for convenience
#You are welcome to return an xcode project or visual studio project file instead
cmake_minimum_required(VERSION 3.23)

project(
  BestItemProblem
  VERSION 1.0
  LANGUAGES CXX)

add_executable(BestItemProblem
                src/catch2/catch.hpp
                src/main.cpp
                src/itemSelector.h
                src/itemSelector.cpp
                src/itemSelectorTest.cpp
                src/dataTypes.h
                src/utils.h
                #Add any additional files here
)

set_target_properties(BestItemProblem PROPERTIES
  CXX_STANDARD 17
  CXX_EXTENSIONS OFF
)

include_directories(src)