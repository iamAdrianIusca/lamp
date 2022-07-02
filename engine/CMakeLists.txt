project(engine)

add_library(${PROJECT_NAME})

target_precompile_headers(${PROJECT_NAME}  PUBLIC stl.hpp)
target_include_directories(${PROJECT_NAME} PUBLIC . ${BULLET_PHYSICS_SOURCE_DIR}/src)
target_link_libraries(${PROJECT_NAME}      PUBLIC BulletCollision LinearMath assimp glm)

target_sources(${PROJECT_NAME} PRIVATE window.cpp shader.cpp shader_stage.cpp buffer.cpp time.cpp file.cpp vertex_array.cpp
                                       object.cpp importer.cpp mesh.cpp model.cpp physics.cpp)
if (LAMP_WIN32)
    find_package(Vulkan)
    target_link_libraries(${PROJECT_NAME} PUBLIC Vulkan::Vulkan glfw glad)
endif()