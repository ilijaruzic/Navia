#ifndef _SUB_TEXTURE_HPP_
#define _SUB_TEXTURE_HPP_

#include "navia/core/Base.hpp"
#include "navia/renderer/Texture.hpp"
#include <glm/glm.hpp>

namespace Navia {
class SubTexture2D {
public:
    SubTexture2D(Ref<Texture2D> texture, const glm::vec2& min, const glm::vec2& max);

    const Ref<Texture2D> getTexture() const;
    const glm::vec2* getTextureCoords() const;

    static Ref<SubTexture2D> create(Ref<Texture2D> texture, const glm::vec2& coords, const glm::vec2& cellSize, const glm::vec2& spriteSize = glm::vec2{ 1.0f });

private:
    Ref<Texture2D> texture;
    glm::vec2 textureCoords[4];
};
}

#endif