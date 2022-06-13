project(engine)

add_library(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC .)
target_link_libraries(${PROJECT_NAME}      PRIVATE glfw glad)

target_sources(${PROJECT_NAME} PRIVATE window.cpp shader.cpp shader_stage.cpp buffer.cpp time.cpp file.cpp)