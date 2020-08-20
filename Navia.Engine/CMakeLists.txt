cmake_minimum_required(VERSION 3.17)
project(Navia.Engine VERSION 1.0 DESCRIPTION "Navia game engine library" LANGUAGES CXX)

add_compile_options(/EHsc)
add_compile_definitions(_CRT_SECURE_NO_WARNINGS GLFW_INLUDE_NONE)

set(CMAKE_CXX_STANDARD 20)
set(SOURCE_FILES
        src/Application.cpp)
set(INCLUDE_FILES
        include/Application.hpp
        include/Core.hpp)

add_subdirectory(lib/glfw)
add_subdirectory(lib/glm)

add_library(Navia.Engine STATIC ${SOURCE_FILES})
target_include_directories(Navia.Engine
        PUBLIC
            include
            lib/glm
            lib/spdlog/include
        PRIVATE
            lib/glad/include
            lib/glfw/include
            lib/imgui
            lib/stb_image)