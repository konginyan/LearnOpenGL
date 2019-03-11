cmake_minimum_required(VERSION 2.6)

project(Ace)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

include_directories(./include)
include_directories(./src)

find_library(GLFW glfw3 ./lib NO_DEFAULT_PATH)

link_libraries(${GLFW})

add_subdirectory(./src)