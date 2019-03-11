add_executable(${PROJECT_NAME} render.cpp)

target_link_libraries(${PROJECT_NAME}
    render
    runtime
    interaction
)