cmake_minimum_required(VERSION 3.17)
project(Navia.Engine VERSION 1.0 DESCRIPTION "Navia game engine library" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_SKIP_RULE_DEPENDENCY TRUE)
set(SOURCE_FILES
        src/core/Application.cpp
        src/core/Layer.cpp
        src/core/LayerStack.cpp
        src/core/Logger.cpp
        src/core/OrthographicCameraController.cpp
        src/core/Timestep.cpp
        src/core/Window.cpp
        src/debug/Instrumentor.cpp
        src/events/ApplicationEvent.cpp
        src/events/Event.cpp
        src/events/KeyEvent.cpp
        src/events/MouseEvent.cpp
        src/events/WindowEvent.cpp
        src/imgui/ImGuiBuild.cpp
        src/imgui/ImGuiLayer.cpp
        src/platform/opengl/OpenGLFramebuffer.cpp
        src/platform/opengl/OpenGLGraphicsContext.cpp
        src/platform/opengl/OpenGLIndexBuffer.cpp
        src/platform/opengl/OpenGLRendererAPI.cpp
        src/platform/opengl/OpenGLShader.cpp
        src/platform/opengl/OpenGLTexture.cpp
        src/platform/opengl/OpenGLVertexArray.cpp
        src/platform/opengl/OpenGLVertexBuffer.cpp
        src/platform/windows/WindowsInput.cpp
        src/platform/windows/WindowsWindow.cpp
        src/renderer/BufferLayout.cpp
        src/renderer/Camera.cpp
        src/renderer/Framebuffer.cpp
        src/renderer/GraphicsContext.cpp
        src/renderer/IndexBuffer.cpp
        src/renderer/OrthographicCamera.cpp
        src/renderer/RenderCommand.cpp
        src/renderer/Renderer.cpp
        src/renderer/Renderer2D.cpp
        src/renderer/RendererAPI.cpp
        src/renderer/Shader.cpp
        src/renderer/ShaderLibrary.cpp
        src/renderer/Texture.cpp
        src/renderer/VertexArray.cpp
        src/renderer/VertexBuffer.cpp
        src/scene/Components.cpp
        src/scene/Entity.cpp
        src/scene/Scene.cpp
        src/scene/ScriptableEntity.cpp
        src/scene/SceneCamera.cpp)
set(INCLUDE_FILES
        include/navia/core/Application.hpp
        include/navia/core/Base.hpp
        include/navia/core/Input.hpp
        include/navia/core/KeyCodes.hpp
        include/navia/core/Layer.hpp
        include/navia/core/LayerStack.hpp
        include/navia/core/Logger.hpp
        include/navia/core/MouseCodes.hpp
        include/navia/core/OrthographicCameraController.hpp
        include/navia/core/Timestep.hpp
        include/navia/core/Window.hpp
        include/navia/debug/Instrumentor.hpp
        include/navia/events/ApplicationEvent.hpp
        include/navia/events/Event.hpp
        include/navia/events/KeyEvent.hpp
        include/navia/events/MouseEvent.hpp
        include/navia/events/WindowEvent.hpp
        include/navia/imgui/ImGuiLayer.hpp
        include/navia/platform/opengl/OpenGLFramebuffer.hpp
        include/navia/platform/opengl/OpenGLGraphicsContext.hpp
        include/navia/platform/opengl/OpenGLIndexBuffer.hpp
        include/navia/platform/opengl/OpenGLRendererAPI.hpp
        include/navia/platform/opengl/OpenGLShader.hpp
        include/navia/platform/opengl/OpenGLTexture.hpp
        include/navia/platform/opengl/OpenGLVertexArray.hpp
        include/navia/platform/opengl/OpenGLVertexBuffer.hpp
        include/navia/platform/windows/WindowsWindow.hpp
        include/navia/renderer/BufferLayout.hpp
        include/navia/renderer/Camera.hpp
        include/navia/renderer/Framebuffer.hpp
        include/navia/renderer/GraphicsContext.hpp
        include/navia/renderer/IndexBuffer.hpp
        include/navia/renderer/OrthographicCamera.hpp
        include/navia/renderer/RenderCommand.hpp
        include/navia/renderer/Renderer.hpp
        include/navia/renderer/Renderer2D.hpp
        include/navia/renderer/RendererAPI.hpp
        include/navia/renderer/Shader.hpp
        include/navia/renderer/ShaderLibrary.hpp
        include/navia/renderer/Texture.hpp
        include/navia/renderer/VertexArray.hpp
        include/navia/renderer/VertexBuffer.hpp
        include/navia/scene/Components.hpp
        include/navia/scene/Entity.hpp
        include/navia/scene/Scene.hpp
        include/navia/scene/SceneCamera.hpp
        include/navia/scene/ScriptableEntity.hpp
        PrecompiledHeaders.hpp)

add_subdirectory(lib/entt)
add_subdirectory(lib/imgui)
add_subdirectory(lib/glad)
add_subdirectory(lib/glfw)
add_subdirectory(lib/glm)
add_subdirectory(lib/stb)

add_library(Navia.Engine STATIC ${SOURCE_FILES} ${INCLUDE_FILES})
target_link_libraries(Navia.Engine PUBLIC imgui PRIVATE opengl32 glad glfw)
target_precompile_headers(Navia.Engine PUBLIC PrecompiledHeaders.hpp)
target_include_directories(Navia.Engine
        PUBLIC
            include
            lib/entt/single_include
            lib/glm
            lib/imgui
            lib/spdlog/include
        PRIVATE
            lib/glad/include
            lib/glfw/include
            lib/stb)

if(WIN32)
    if(CMAKE_SIZEOF_VOID_P EQUAL 4)
        target_compile_definitions(Navia.Engine PUBLIC NAVIA_PLATFORM_WINDOWS)
    elseif()
        message(FATAL_ERROR "x86 builds are not supported!")
    endif()
elseif(APPLE)
    target_compile_definitions(Navia.Engine PUBLIC NAVIA_PLATFORM_MACOS)
    message(FATAL_ERROR "macOS is not supported!")
    if(IOS)
        target_compile_definitions(Navia.Engine PUBLIC NAVIA_PLATFORM_IOS)
        message(FATAL_ERROR "iOS is not supported!")
    endif()
elseif(ANDROID)
    target_compile_definitions(Navia.Engine PUBLIC NAVIA_PLATFORM_ANDROID)
    message(FATAL_ERROR "Android is not supported!")
elseif(UNIX AND NOT APPLE)
    set(LINUX TRUE)
    if (LINUX)
        target_compile_definitions(Navia.Engine PUBLIC NAVIA_PLATFORM_LINUX)
        message(FATAL_ERROR "Linux is not supported!")
    endif()
else()
    message(FATAL_ERROR "Unsuported platform!")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(Navia.Engine PUBLIC NAVIA_DEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(Navia.Engine PUBLIC NAVIA_RELEASE)
endif()

target_compile_options(Navia.Engine PUBLIC /EHsc)
target_compile_definitions(Navia.Engine
        PUBLIC
            GLM_FORCE_SILENT_WARNINGS
            STB_IMAGE_IMPLEMENTATION
        PRIVATE
            GLFW_INCLUDE_NONE)