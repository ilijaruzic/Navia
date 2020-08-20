cmake_minimum_required(VERSION 3.17)
project(Navia VERSION 1.0 DESCRIPTION "Navia game engine" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Navia.Engine)
add_subdirectory(Navia.Sandbox)