cmake_minimum_required(VERSION 3.5)
project(LLM-Assist-Clip)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)  # Set C++ standard to C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Ensure C++17 is available, fail otherwise
set(CMAKE_CXX_EXTENSIONS OFF)  # Use -std=c++17 instead of -std=gnu++17

find_package(Qt5Core REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
