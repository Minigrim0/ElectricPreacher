add_library(
    Game
    src/game.cpp
)

target_link_libraries(Game PUBLIC MapManaging)
target_link_libraries(Game PUBLIC Player)

target_include_directories(Game PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/MapManaging"
                          "${PROJECT_SOURCE_DIR}/Player"
)
