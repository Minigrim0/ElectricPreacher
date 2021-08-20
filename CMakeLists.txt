cmake_minimum_required(VERSION 3.10)

project(ElectricPreacher VERSION 0.0.1)

if (WIN32)
    find_file(SDL2_INCLUDE_DIR NAME SDL.h HINTS SDL2)
    find_library(SDL2_LIBRARY NAME SDL2)
endif (WIN32)
if (UNIX)
    find_package(SDL2 REQUIRED)
endif(UNIX)

include_directories(${SDL2_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(constants.hpp.in constants.hpp)

add_subdirectory(src/map)
add_subdirectory(src/UI)
add_subdirectory(src/screen)

add_executable(ElectricPreacher main.cpp)

target_link_libraries(ElectricPreacher PUBLIC ${SDL2_LIBRARY})

target_link_libraries(ElectricPreacher PUBLIC MapManaging)
target_link_libraries(ElectricPreacher PUBLIC UserInterface)
target_link_libraries(ElectricPreacher PUBLIC Screen)

target_include_directories(ElectricPreacher PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/MapManaging"
                          "${PROJECT_SOURCE_DIR}/UserInterface"
                          "${PROJECT_SOURCE_DIR}/Screen"
                          )
