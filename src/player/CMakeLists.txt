add_library(
    Player
    src/player.cpp
)

target_include_directories(Player PUBLIC
                          "${PROJECT_BINARY_DIR}"
)
