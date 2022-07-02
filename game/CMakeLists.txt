project(lamp)

add_executable(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PRIVATE engine)
target_sources(${PROJECT_NAME}        PRIVATE main.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES
                                      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build")
if (LAMP_WEB)
    set_target_properties(${PROJECT_NAME} PROPERTIES
                                          SUFFIX     ".html"
                                          LINK_FLAGS "-s USE_GLFW=3 -O3      \
                                                      -s ALLOW_MEMORY_GROWTH \
                                                      -s MIN_WEBGL_VERSION=2 \
                                                     --preload-file ${CMAKE_SOURCE_DIR}/build/web/assets@/assets"
                                          RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/web")
endif()