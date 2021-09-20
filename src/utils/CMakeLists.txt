add_library(
    Utils
    src/build_windows.cpp
    src/utils.cpp
)

target_include_directories(Utils PUBLIC
                          "${PROJECT_BINARY_DIR}"
)
