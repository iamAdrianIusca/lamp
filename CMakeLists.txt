cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)

option(LAMP_WIN32 "lamp windows platform switch" OFF)
option(LAMP_WEB   "lamp web platform switch"     OFF)

if (LAMP_WIN32)
    add_compile_definitions(LAMP_WIN32)
elseif(LAMP_WEB)
    add_compile_definitions(LAMP_WEB)
endif()

add_subdirectory(libraries)
add_subdirectory(engine)
add_subdirectory(game)