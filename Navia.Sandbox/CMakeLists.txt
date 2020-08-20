cmake_minimum_required(VERSION 3.17)
project(Navia.Sandbox VERSION 1.0 DESCRIPTION "Navia game engine application" LANGUAGES CXX)

add_compile_options(/EHsc)

set(CMAKE_CXX_STANDARD 20)
set(SOURCE_FILES
        src/SandboxApplication.cpp )
set(INCLUDE_FILES
        include/SandboxApplication.hpp)

add_executable(Navia.Sandbox ${SOURCE_FILES})
target_link_libraries(Navia.Sandbox PUBLIC Navia.Engine)
target_include_directories(Navia.Sandbox PRIVATE include)