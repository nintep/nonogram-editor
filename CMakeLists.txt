cmake_minimum_required(VERSION 3.22.0)

project(nonogram-editor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)

file(GLOB_RECURSE SOURCES
    src/*.cpp
    src/*.h
)

add_executable(nonogram-editor ${SOURCES})

# Find the Qt5 package and link libraries
find_package(Qt5 REQUIRED COMPONENTS Widgets)
target_link_libraries(nonogram-editor PRIVATE Qt5::Widgets)