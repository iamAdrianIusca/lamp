project(test)

add_subdirectory(libraries)
add_subdirectory(engine)

find_package(Vulkan)

add_executable(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PRIVATE Vulkan::Vulkan glfw glad engine)

target_sources(${PROJECT_NAME} PRIVATE main.cpp)