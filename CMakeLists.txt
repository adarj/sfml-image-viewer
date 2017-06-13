cmake_minimum_required (VERSION 3.8.2)
project (sfml-image-viewer)

file (GLOB SOURCES "src/*.cpp")

add_executable (sfml-image-viewer ${SOURCES})
