cmake_minimum_required(VERSION 3.17)
project(Navia.Engine VERSION 1.0 DESCRIPTION "Navia game engine library" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_SKIP_RULE_DEPENDENCY TRUE)
set(SOURCE_FILES
        src/events/ApplicationEvent.cpp
        src/events/Event.cpp
        src/events/KeyEvent.cpp
        src/events/MouseEvent.cpp
        src/events/WindowEvent.cpp
        src/imgui/ImGuiBuild.cpp
        src/imgui/ImGuiLayer.cpp
        src/platform/opengl/OpenGLGraphicsContext.cpp
        src/platform/opengl/OpenGLIndexBuffer.cpp
        src/platform/opengl/OpenGLRendererAPI.cpp
        src/platform/opengl/OpenGLShader.cpp
        src/platform/opengl/OpenGLVertexArray.cpp
        src/platform/opengl/OpenGLVertexBuffer.cpp
        src/platform/windows/WindowsInput.cpp
        src/platform/windows/WindowsWindow.cpp
        src/renderer/BufferLayout.cpp
        src/renderer/GraphicsContext.cpp
        src/renderer/IndexBuffer.cpp
        src/renderer/OrthographicCamera.cpp
        src/renderer/RenderCommand.cpp
        src/renderer/Renderer.cpp
        src/renderer/RendererAPI.cpp
        src/renderer/Shader.cpp
        src/renderer/VertexArray.cpp
        src/renderer/VertexBuffer.cpp
        src/Application.cpp
        src/Input.cpp
        src/Layer.cpp
        src/LayerStack.cpp
        src/Logger.cpp
        src/Timestep.cpp
        src/Window.cpp)
set(INCLUDE_FILES
        include/navia/core/Application.hpp
        include/navia/core/Core.hpp
        include/navia/core/Input.hpp
        include/navia/core/KeyCodes.hpp
        include/navia/core/Layer.hpp
        include/navia/core/LayerStack.hpp
        include/navia/core/Logger.hpp
        include/navia/core/MouseButtons.hpp
        include/navia/core/Timestep.hpp
        include/navia/core/Window.hpp
        include/navia/events/ApplicationEvent.hpp
        include/navia/events/Event.hpp
        include/navia/events/KeyEvent.hpp
        include/navia/events/MouseEvent.hpp
        include/navia/events/WindowEvent.hpp
        include/navia/imgui/ImGuiLayer.hpp
        include/navia/platform/opengl/OpenGLGraphicsContext.hpp
        include/navia/platform/opengl/OpenGLIndexBuffer.hpp
        include/navia/platform/opengl/OpenGLRendererAPI.hpp
        include/navia/platform/opengl/OpenGLShader.hpp
        include/navia/platform/opengl/OpenGLVertexArray.hpp
        include/navia/platform/opengl/OpenGLVertexBuffer.hpp
        include/navia/platform/windows/WindowsInput.hpp
        include/navia/platform/windows/WindowsWindow.hpp
        include/navia/renderer/BufferLayout.hpp
        include/navia/renderer/GraphicsContext.hpp
        include/navia/renderer/IndexBuffer.hpp
        include/navia/renderer/OrthographicCamera.hpp
        include/navia/renderer/RenderCommand.hpp
        include/navia/renderer/Renderer.hpp
        include/navia/renderer/RendererAPI.hpp
        include/navia/renderer/Shader.hpp
        include/navia/renderer/VertexArray.hpp
        include/navia/renderer/VertexBuffer.hpp
        PrecompiledHeaders.hpp)

add_subdirectory(lib/imgui)
add_subdirectory(lib/glad)
add_subdirectory(lib/glfw)
add_subdirectory(lib/glm)

add_library(Navia.Engine STATIC ${SOURCE_FILES} ${INCLUDE_FILES})
target_link_libraries(Navia.Engine PRIVATE imgui opengl32 glad glfw)
target_precompile_headers(Navia.Engine PUBLIC PrecompiledHeaders.hpp)
target_include_directories(Navia.Engine
        PUBLIC
            include
            lib/glm
            lib/imgui
            lib/spdlog/include
        PRIVATE
            lib/glad/include
            lib/glfw/include
            lib/stb)

if(WIN32)
    target_compile_definitions(Navia.Engine PUBLIC NAVIA_PLATFORM_WINDOWS GLFW_INCLUDE_NONE)
else()
    message("Unsuported platform")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(Navia.Engine PUBLIC NAVIA_DEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(Navia.Engine PUBLIC NAVIA_RELEASE)
endif()

target_compile_options(Navia.Engine PUBLIC /EHsc)
target_compile_definitions(Navia.Engine PUBLIC GLM_FORCE_SILENT_WARNINGS)