add_library(
    Screen
    src/screen.cpp
    src/notification.cpp
    src/notification_center.cpp
    src/image_set.cpp
)

target_include_directories(Screen PUBLIC
                          "${PROJECT_BINARY_DIR}"
)