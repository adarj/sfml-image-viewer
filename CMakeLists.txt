cmake_minimum_required (VERSION 3.8.2)
project (sfml-image-viewer)

file (GLOB SOURCES "src/*.cpp")

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
add_executable (sfml-image-viewer ${SOURCES})
