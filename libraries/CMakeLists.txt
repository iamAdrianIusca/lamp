set(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
set(ASSIMP_BUILD_TESTS        OFF)
set(ASSIMP_NO_EXPORT          ON)

set(GLFW_BUILD_DOCS     OFF)
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS    OFF)

set(BUILD_UNIT_TESTS    OFF)
set(BUILD_CPU_DEMOS     OFF)
set(BUILD_EXTRAS        OFF)
set(BUILD_BULLET2_DEMOS OFF)

add_subdirectory(glfw)
add_subdirectory(glad)
add_subdirectory(glm)
add_subdirectory(assimp)
add_subdirectory(bullet3)