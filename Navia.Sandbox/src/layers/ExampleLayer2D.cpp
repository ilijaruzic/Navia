#include "layers/ExampleLayer2D.hpp"
#include <navia/platform/opengl/OpenGLShader.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

ExampleLayer2D::ExampleLayer2D() : Navia::Layer("ExampleLayer2D") {}

void ExampleLayer2D::onAttach() {
    vertexArray = Navia::VertexArray::create();

    float vertices[5 * 4]{
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };
    Navia::Ref<Navia::VertexBuffer> vertexBuffer = Navia::VertexBuffer::create(vertices, sizeof(vertices));
    Navia::BufferLayout layout{
        { Navia::ShaderDatatype::Float3, "v_inPosition" }
    };
    vertexBuffer->setLayout(layout);
    vertexArray->addVertexBuffer(vertexBuffer);

    size_t indices[6]{
        0, 1, 2, 2, 3, 0
    };
    Navia::Ref<Navia::IndexBuffer> indexBuffer = Navia::IndexBuffer::create(indices, sizeof(indices) / sizeof(size_t));
    vertexArray->setIndexBuffer(indexBuffer);

    shader = Navia::Shader::create("assets/shaders/flatColor.glsl");
}

void ExampleLayer2D::onDetach() {

}

void ExampleLayer2D::onImGuiRender() {
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(squareColor));
    ImGui::End();
}

void ExampleLayer2D::onUpdate(Navia::Timestep timestep) {
    cameraController.onUpdate(timestep);

    Navia::RenderCommand::setClearColor(glm::vec4{ 0.0f, 0.0f, 0.0f, 1.0f });
    Navia::RenderCommand::clear();

    Navia::Renderer::beginScene(cameraController.getCamera());

    glm::mat4 scale = glm::scale(glm::mat4{ 1.0f }, glm::vec3{ 0.1f });
    std::dynamic_pointer_cast<Navia::OpenGLShader>(shader)->bind();
    std::dynamic_pointer_cast<Navia::OpenGLShader>(shader)->uploadUniformFloat4("f_uColor", squareColor);
    Navia::Renderer::submit(shader, vertexArray, glm::scale(glm::mat4{ 1.0f }, glm::vec3{ 1.5f }));

    Navia::Renderer::endScene();
}

void ExampleLayer2D::onEvent(Navia::Event& event) {
    cameraController.onEvent(event);
}
