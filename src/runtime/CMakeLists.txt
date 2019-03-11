file(GLOB SRC_FILES ./*.c ./*.cpp)

add_library(runtime STATIC ${SRC_FILES})

target_link_libraries(runtime render)