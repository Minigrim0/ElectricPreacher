cmake_minimum_required(VERSION 3.10)

# set the project name
project(ElectricPreacher VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(src/constants/constants.hpp.in src/constants/constants.hpp)

add_subdirectory(src/map)
add_subdirectory(src/UI)

add_executable(ElectricPreacher main.cpp)

target_link_libraries(ElectricPreacher PUBLIC MapManaging)
target_link_libraries(ElectricPreacher PUBLIC UserInterface)

target_include_directories(ElectricPreacher PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/MapManaging"
                          )
