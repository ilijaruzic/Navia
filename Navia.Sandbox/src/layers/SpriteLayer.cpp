#include "layers/SpriteLayer.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

static const size_t mapTilesWidth = 24;
static const char* mapTiles{
    "WWWWWWWWWWWWWWWWWWWWWWWW"
    "WWWWWWWDDDDDDWWWWWBBWWWW"
    "WWWWWDDDDDDDDDDDDWWWWWWW"
    "WWWWDDDDDDDDTDDDDDWWWWWW"
    "WWWDDDDDDDDDDDDDDDDDWWWW"
    "WWDDDDWWWDDDDDDDDDDDWWWW"
    "WDDTDDWWWDDDDDTDDDDDDWWW"
    "WWDDDDDDDDDDDDDDDDDDWWWW"
    "WWWDDDDDDDDDDDDDDDDWWWWW"
    "WWWWDDDDDDTTDDDDDDWWWWWW"
    "WWWWWDDDDDDDDDDDWWWWBWWW"
    "WWWWWWWWWDDDDDWWWWWWWWWW"
    "WWBWWWWWWWWWWWWWWWWWWWWW"
    "WWWWWWWWWWWWWWWWWWWWWWWW"
};

SpriteLayer::SpriteLayer() : Navia::Layer("SpriteLayer") {}

void SpriteLayer::onAttach() {
    NAVIA_PROFILE_FUNCTION();

    rpgSpriteSheet = Navia::Texture2D::create("assets/game/textures/rpg_sprite_sheet.png");
    stairsTexture = Navia::SubTexture2D::create(rpgSpriteSheet, glm::vec2{ 7.0f, 6.0f }, glm::vec2{ 128.0f, 128.0f });
    textureMapWidth = mapTilesWidth;
    textureMapHeight = std::strlen(mapTiles) / mapTilesWidth;
    texturesMap['B'] = Navia::SubTexture2D::create(rpgSpriteSheet, glm::vec2{ 8.0f, 2.0f }, glm::vec2{ 128.0f, 128.0f });
    texturesMap['D'] = Navia::SubTexture2D::create(rpgSpriteSheet, glm::vec2{  6.0f, 11.0f }, glm::vec2{ 128.0f, 128.0f });
    texturesMap['T'] = Navia::SubTexture2D::create(rpgSpriteSheet, glm::vec2{ 2.0f, 1.0f }, glm::vec2{ 128.0f, 128.0f }, glm::vec2{ 1.0f, 2.0f });
    texturesMap['W'] = Navia::SubTexture2D::create(rpgSpriteSheet, glm::vec2{ 11.0f, 11.0f }, glm::vec2{ 128.0f, 128.0f });

    cameraController.setZoomLevel(5.0f);
}

void SpriteLayer::onDetach() {
    NAVIA_PROFILE_FUNCTION();


}

void SpriteLayer::onImGuiRender() {
    NAVIA_PROFILE_FUNCTION();

    auto statistics = Navia::Renderer2D::getStatistics();
    ImGui::Begin("Statistics");
    ImGui::SetWindowSize(ImVec2(200.0f, 200.0f));
    ImGui::Text("Draw Calls: %d", statistics.drawCallCount);
    ImGui::Text("Quads: %d", statistics.quadCount);
    ImGui::Text("Vertices: %d", statistics.getVertexCount());
    ImGui::Text("Indices: %d", statistics.getIndexCount());
    ImGui::End();
}

void SpriteLayer::onUpdate(Navia::Timestep timestep) {
    NAVIA_PROFILE_FUNCTION();

    cameraController.onUpdate(timestep);

    Navia::Renderer2D::resetStatistics();
    {
        NAVIA_PROFILE_SCOPE("Navia::RenderCommand initial setup");

        Navia::RenderCommand::setClearColor(glm::vec4{ 0.0f, 0.0f, 0.0f, 1.0f });
        Navia::RenderCommand::clear();
    }

    {
        NAVIA_PROFILE_SCOPE("Navia::Renderere2D draws");

        Navia::Renderer2D::beginScene(cameraController.getCamera());
        for (size_t y = 0; y < textureMapHeight; ++y) {
            for (size_t x = 0; x < textureMapWidth; ++x) {
                char tileType = mapTiles[x + y * textureMapWidth];
                Navia::Ref<Navia::SubTexture2D> texture;
                if (texturesMap.find(tileType) != texturesMap.end()) {
                    texture = texturesMap[tileType];
                }
                else {
                    texture = stairsTexture;
                }
                Navia::Renderer2D::drawQuad(glm::vec3{ x - textureMapWidth / 2.0f, textureMapHeight - y - textureMapHeight / 2.0f, 0.5f }, glm::vec2{ 1.0f, 1.0f }, texture);
            }
        }
        // Navia::Renderer2D::drawQuad(glm::vec3{  1.0f, 0.0f, 0.5f }, glm::vec2{ 1.0f, 1.0f }, stairsTexture);
        Navia::Renderer2D::endScene();
    }
}

void SpriteLayer::onEvent(Navia::Event& event) {
    cameraController.onEvent(event);
}