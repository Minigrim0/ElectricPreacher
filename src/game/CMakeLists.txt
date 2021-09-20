add_library(
    Game
    src/game.cpp
)

target_include_directories(Game PUBLIC
                          "${PROJECT_BINARY_DIR}"
)
