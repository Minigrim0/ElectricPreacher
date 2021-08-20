add_library(
    UserInterface
    src/button.cpp
    src/container.cpp
    src/text_input.cpp
)

target_include_directories(UserInterface PUBLIC
                          "${PROJECT_BINARY_DIR}"
)