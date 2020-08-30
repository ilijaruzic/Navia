cmake_minimum_required(VERSION 3.17)
project(Navia.Sandbox VERSION 1.0 DESCRIPTION "Navia game engine application" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_SKIP_RULE_DEPENDENCY TRUE)
set(SOURCE_FILES
        src/layers/ExampleLayer.cpp
        src/layers/ExampleLayer2D.cpp
        src/SandboxApplication.cpp)
set(INCLUDE_FILES
        include/layers/ExampleLayer.hpp
        include/layers/ExampleLayer2D.hpp
        include/SandboxApplication.hpp)

add_executable(Navia.Sandbox ${SOURCE_FILES} ${INCLUDE_FILES})
target_link_libraries(Navia.Sandbox PUBLIC Navia.Engine)
target_include_directories(Navia.Sandbox
        PRIVATE
            include)

target_compile_options(Navia.Sandbox PUBLIC /EHsc)
target_compile_definitions(Navia.Sandbox PUBLIC GLM_FORCE_SILENT_WARNINGS)