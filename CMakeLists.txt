cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)

project(test)

add_subdirectory(libraries)
add_subdirectory(engine)

find_package(Vulkan)

add_executable(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PRIVATE Vulkan::Vulkan engine)

target_sources(${PROJECT_NAME} PRIVATE main.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES
                                      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build")