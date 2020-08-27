#include "layers/ExampleLayer.hpp"
#include <navia/platform/opengl/OpenGLShader.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

ExampleLayer::ExampleLayer() : Navia::Layer("ExampleLayer") {
    // Squares
    {
        squareVertexArray = Navia::VertexArray::create();

        float squareVertices[5 * 4]{
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
        };
        Navia::Ref<Navia::VertexBuffer> squareVertexBuffer = Navia::VertexBuffer::create(squareVertices, sizeof(squareVertices));
        Navia::BufferLayout squareLayout{
            { Navia::ShaderDatatype::Float3, "inPosition" },
            { Navia::ShaderDatatype::Float2, "inTextureCoords" }
        };
        squareVertexBuffer->setLayout(squareLayout);
        squareVertexArray->addVertexBuffer(squareVertexBuffer);

        size_t squareIndices[6]{
                0, 1, 2, 2, 3, 0
        };
        Navia::Ref<Navia::IndexBuffer> squareIndexBuffer = Navia::IndexBuffer::create(squareIndices, sizeof(squareIndices) / sizeof(size_t));
        squareVertexArray->setIndexBuffer(squareIndexBuffer);

        std::string squareFlatColorVertexSource{R"(
            #version 330 core

            layout(location = 0) in vec3 v_inPosition;

            uniform mat4 v_uViewProjection;
            uniform mat4 v_uTransform;

            out vec3 v_outPosition;

            void main() {
                v_outPosition = v_inPosition;
                gl_Position = v_uViewProjection * v_uTransform * vec4(v_inPosition, 1.0);
            }
        )"};
        std::string squareFlatColorFragmentSource{R"(
            #version 330 core

            layout(location = 0) out vec4 f_outColor;

            uniform vec3 f_uColor;

            in vec3 v_outPosition;

            void main() {
                f_outColor = vec4(f_uColor, 1.0);
            }
        )"};
        squareFlatColorShader = Navia::Shader::create("squareFlatColorShader", squareFlatColorVertexSource, squareFlatColorFragmentSource);
        auto squareTextureShader = shaderLibrary.load("assets/shaders/texture.glsl");
        checkerboardTexture = Navia::Texture2D::create("assets/textures/checkerboard.png");
        googleTexture = Navia::Texture2D::create("assets/textures/google.png");
        std::dynamic_pointer_cast<Navia::OpenGLShader>(squareTextureShader)->bind();
        std::dynamic_pointer_cast<Navia::OpenGLShader>(squareTextureShader)->uploadUniformInt("f_uTexture", 0);
    }
    // Triangle
    {
        triangleVertexArray = Navia::VertexArray::create();

        float triangleVertices[3 * 7]{
            -0.5f, -0.5f, 0.0f, 0.75f, 0.25f, 0.25f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.25f, 0.75f, 0.25f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.25f, 0.25f, 0.75f, 1.0f
        };
        Navia::Ref<Navia::VertexBuffer> triangleVertexBuffer;
        triangleVertexBuffer = Navia::VertexBuffer::create(triangleVertices, sizeof(triangleVertices));
        Navia::BufferLayout triangleLayout{
            { Navia::ShaderDatatype::Float3, "inPosition" },
            { Navia::ShaderDatatype::Float4, "inColor" }
        };
        triangleVertexBuffer->setLayout(triangleLayout);
        triangleVertexArray->addVertexBuffer(triangleVertexBuffer);

        size_t triangleIndices[3]{
                0, 1, 2
        };
        Navia::Ref<Navia::IndexBuffer> triangleIndexBuffer;
        triangleIndexBuffer = Navia::IndexBuffer::create(triangleIndices, sizeof(triangleIndices) / sizeof(size_t));
        triangleVertexArray->setIndexBuffer(triangleIndexBuffer);

        std::string triangleVertexSource{R"(
            #version 330 core

            layout(location = 0) in vec3 v_inPosition;
            layout(location = 1) in vec4 v_inColor;

            uniform mat4 v_uViewProjection;
            uniform mat4 v_uTransform;

            out vec3 v_outPosition;
            out vec4 v_outColor;

            void main() {
                v_outPosition = v_inPosition;
                v_outColor = v_inColor;
                gl_Position = v_uViewProjection * v_uTransform * vec4(v_inPosition, 1.0);
            }
        )"};
        std::string triangleFragmentSource{R"(
            #version 330 core

            layout(location = 0) out vec4 f_outColor;

            in vec3 v_outPosition;
            in vec4 v_outColor;

            void main() {
                f_outColor = vec4(v_outPosition * 0.5 + 0.5, 1.0);
                f_outColor = v_outColor;
            }
        )"};
        triangleShader = Navia::Shader::create("triangleShader", triangleVertexSource, triangleFragmentSource);
    }
}

void ExampleLayer::onImGuiRender() {
    ImGui::Begin("Settings");
    ImGui::ColorEdit3("Square Color", glm::value_ptr(squareColor));
    ImGui::End();
}

void ExampleLayer::onUpdate(Navia::Timestep timestep) {
    if (Navia::Input::isKeyPressed(NAVIA_KEY_A)) {
        cameraPosition.x -= cameraMovementSpeed * timestep;
    }
    else if (Navia::Input::isKeyPressed(NAVIA_KEY_D)) {
        cameraPosition.x += cameraMovementSpeed * timestep;
    }
    if (Navia::Input::isKeyPressed(NAVIA_KEY_S)) {
        cameraPosition.y -= cameraMovementSpeed * timestep;
    }
    else if (Navia::Input::isKeyPressed(NAVIA_KEY_W)) {
        cameraPosition.y += cameraMovementSpeed * timestep;
    }

    if (Navia::Input::isKeyPressed(NAVIA_KEY_Q)) {
        cameraRotation += cameraRotationSpeed * timestep;
    }
    else if (Navia::Input::isKeyPressed(NAVIA_KEY_E)) {
        cameraRotation -= cameraRotationSpeed * timestep;
    }

    Navia::RenderCommand::setClearColor(glm::vec4{ 0.0f, 0.0f, 0.0f, 1.0f });
    Navia::RenderCommand::clear();

    camera.setPosition(cameraPosition);
    camera.setRotation(cameraRotation);

    Navia::Renderer::beginScene(camera);

    glm::mat4 scale = glm::scale(glm::mat4{ 1.0f }, glm::vec3{ 0.1f });
    std::dynamic_pointer_cast<Navia::OpenGLShader>(squareFlatColorShader)->bind();
    std::dynamic_pointer_cast<Navia::OpenGLShader>(squareFlatColorShader)->uploadUniformFloat3("f_uColor", squareColor);
    for (size_t j = 0; j < 20; ++j) {
        for (size_t i = 0; i < 20; ++i) {
            glm::vec3 position{i * 0.11f, j * 0.11f, 0.0f};
            glm::mat4 transform = glm::translate(glm::mat4{ 1.0f }, position) * scale;
            Navia::Renderer::submit(squareFlatColorShader, squareVertexArray, transform);
        }
    }
    checkerboardTexture->bind();
    auto squareTextureShader = shaderLibrary.get("texture");
    Navia::Renderer::submit(squareTextureShader, squareVertexArray, glm::scale(glm::mat4{ 1.0f }, glm::vec3{ 1.5f }));
    googleTexture->bind();
    Navia::Renderer::submit(squareTextureShader, squareVertexArray, glm::scale(glm::mat4{ 1.0f }, glm::vec3{ 1.5f }));

    // Navia::Renderer::submit(triangleShader, triangleVertexArray);

    Navia::Renderer::endScene();
}

void ExampleLayer::onEvent(Navia::Event& event) {

}