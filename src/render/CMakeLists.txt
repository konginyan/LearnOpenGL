file(GLOB SRC_FILES ./*.c ./*.cpp)

add_library(render STATIC ${SRC_FILES})