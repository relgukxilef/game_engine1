cmake_minimum_required(VERSION 3.5)

project(game_engine1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(
    game_engine1_opengl STATIC
    source/opengl/pass.cpp
    source/opengl/composition.cpp
    source/opengl/program.cpp
    source/opengl/draw_call.cpp
    source/opengl/vertex_array.cpp
    source/opengl/framebuffer.cpp

    include/ge1/pass.h
    include/ge1/composition.h
    include/ge1/program.h
    include/ge1/draw_call.h
    include/ge1/vertex_array.h
    include/ge1/renderable.h
    include/ge1/resources.h
    include/ge1/span.h
    include/ge1/framebuffer.h
)

add_library(
    game_engine1_vulkan STATIC
    source/vulkan/shader_module.cpp

    include/ge1/span.h
    include/ge1/shader_module.h
)

target_include_directories(
    game_engine1_opengl PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
target_include_directories(
    game_engine1_vulkan PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
