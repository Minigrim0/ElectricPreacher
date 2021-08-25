add_library(
    MapManaging
    src/map_manager.cpp
    src/map_element.cpp
    src/chunk.cpp
)

target_include_directories(MapManaging PUBLIC
                          "${PROJECT_BINARY_DIR}"
)