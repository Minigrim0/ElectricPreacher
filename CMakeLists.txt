cmake_minimum_required(VERSION 3.10)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

project(ElectricPreacher VERSION 0.0.1)

if (WIN32)
    find_file(SDL2_INCLUDE_DIR NAME SDL.h HINTS SDL2)
    find_library(SDL2_LIBRARY NAME SDL2)
endif (WIN32)
if (UNIX)
    find_package(SDL2 REQUIRED)
    find_package(SDL2TTF REQUIRED)
    find_package(SDL2_image REQUIRED)
endif(UNIX)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(constants.hpp.in constants.hpp)

add_subdirectory(src/map)
add_subdirectory(src/UI)
add_subdirectory(src/screen)
add_subdirectory(src/player)
add_subdirectory(src/utils)
add_subdirectory(src/game)

add_executable(ElectricPreacher main.cpp)

target_link_libraries(ElectricPreacher PUBLIC ${SDL2_LIBRARY} ${SDL2TTF_LIBRARY} ${SDL2_IMAGE_LIBRARIES})

target_link_libraries(ElectricPreacher PUBLIC MapManaging)
target_link_libraries(ElectricPreacher PUBLIC UserInterface)
target_link_libraries(ElectricPreacher PUBLIC Screen)
target_link_libraries(ElectricPreacher PUBLIC Player)
target_link_libraries(ElectricPreacher PUBLIC Utils)
target_link_libraries(ElectricPreacher PUBLIC Game)

target_include_directories(ElectricPreacher PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/MapManaging"
                          "${PROJECT_SOURCE_DIR}/UserInterface"
                          "${PROJECT_SOURCE_DIR}/Screen"
                          "${PROJECT_SOURCE_DIR}/Player"
                          "${PROJECT_SOURCE_DIR}/Game"
                          "${PROJECT_SOURCE_DIR}/Utils"
                          )
