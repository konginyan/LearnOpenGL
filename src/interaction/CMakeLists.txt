file(GLOB SRC_FILES ./*.c ./*.cpp)

add_library(interaction STATIC ${SRC_FILES})