cmake_minimum_required(VERSION 3.5)
project(LLM-Assist-Clip)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find Qt packages
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)

# Set current directory and enable AUTOMOC
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

# Add executable target
add_executable(${PROJECT_NAME} main.cpp)

# Link with Qt libraries
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets)

# Add Clip library submodule
# Disable Clip examples and tests
set(CLIP_EXAMPLES OFF CACHE BOOL "Compile clip examples")
set(CLIP_TESTS OFF CACHE BOOL "Compile clip tests")


# Add the clip subdirectory
add_subdirectory(clip)

# Link with the Clip library
target_link_libraries(${PROJECT_NAME} clip)
