cmake_minimum_required(VERSION 3.17)
project(Navia.Editor VERSION 1.0 DESCRIPTION "Navia game engine editor application" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_SKIP_RULE_DEPENDENCY TRUE)
set(SOURCE_FILES
        src/layers/EditorLayer.cpp
        src/EditorApplication.cpp)
set(INCLUDE_FILES
        include/layers/EditorLayer.hpp
        include/EditorApplication.hpp)

add_executable(Navia.Editor ${SOURCE_FILES} ${INCLUDE_FILES})
target_link_libraries(Navia.Editor PUBLIC Navia.Engine)
target_include_directories(Navia.Editor
        PRIVATE
            include)

target_compile_options(Navia.Editor PUBLIC /EHsc)
target_compile_definitions(Navia.Editor PUBLIC GLM_FORCE_SILENT_WARNINGS)