add_library(
    TinyXML
    src/tinyxml2.cpp
)

target_include_directories(TinyXML PUBLIC
                          "${PROJECT_BINARY_DIR}"
)
