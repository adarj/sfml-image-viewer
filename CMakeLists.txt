cmake_minimum_required (VERSION 3.8.2)
project (sfml-image-viewer)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/external/cxxopts/include)
file (GLOB SOURCES "src/*.cpp")

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# Create binary
set (EXECUTABLE_NAME "sfiv")
add_executable (${EXECUTABLE_NAME} ${SOURCES})

# Setup pthreads
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(${EXECUTABLE_NAME} Threads::Threads)

# Setup Boost
find_package(Boost 1.64 REQUIRED COMPONENTS filesystem)
target_link_libraries(${EXECUTABLE_NAME} Boost::filesystem)

# Setup SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED graphics window system)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()
