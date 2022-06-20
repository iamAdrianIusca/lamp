project(engine)

add_library(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC . ${BULLET_PHYSICS_SOURCE_DIR}/src)
target_link_libraries(${PROJECT_NAME}      PUBLIC BulletCollision LinearMath glfw glad glm assimp)

target_sources(${PROJECT_NAME} PRIVATE window.cpp shader.cpp shader_stage.cpp buffer.cpp time.cpp file.cpp vertex_array.cpp
                                       object.cpp importer.cpp mesh.cpp model.cpp physics.cpp)