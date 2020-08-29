#ifndef _SPRITE_LAYER_HPP_
#define _SPRITE_LAYER_HPP_

#include <Navia.hpp>

class SpriteLayer : public Navia::Layer {
public:
    SpriteLayer();

    void onAttach() override;
    void onDetach() override;
    void onImGuiRender() override;
    void onUpdate(Navia::Timestep timestep) override;
    void onEvent(Navia::Event& event) override;

private:
    Navia::OrthographicCameraController cameraController{ 1280.0f / 720.0f, true };

    Navia::Ref<Navia::Shader> shader;
    Navia::Ref<Navia::VertexArray> vertexArray;
    Navia::Ref<Navia::Texture2D> rpgSpriteSheet;
    Navia::Ref<Navia::SubTexture2D> stairsTexture;
    size_t textureMapWidth;
    size_t textureMapHeight;
    std::unordered_map<char, Navia::Ref<Navia::SubTexture2D>> texturesMap;
};

#endif