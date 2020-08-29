#include "navia/renderer/SubTexture.hpp"

namespace Navia {
SubTexture2D::SubTexture2D(Ref<Navia::Texture2D> texture, const glm::vec2& min, const glm::vec2& max) : texture(texture) {
    textureCoords[0] = glm::vec2{ min.x, min.y };
    textureCoords[1] = glm::vec2{ max.x, min.y };
    textureCoords[2] = glm::vec2{ max.x, max.y };
    textureCoords[3] = glm::vec2{ min.x, max.y };
}

const Ref<Texture2D> SubTexture2D::getTexture() const {
    return texture;
}

const glm::vec2* SubTexture2D::getTextureCoords() const {
    return textureCoords;
}

Ref<SubTexture2D> SubTexture2D::create(Ref<Texture2D> texture, const glm::vec2& coords, const glm::vec2& cellSize, const glm::vec2& spriteSize) {
    glm::vec2 min{ ( coords.x                 * cellSize.x) / texture->getWidth(), ( coords.y                 * cellSize.y) / texture->getHeight() };
    glm::vec2 max{ ((coords.x + spriteSize.x) * cellSize.x) / texture->getWidth(), ((coords.y + spriteSize.y) * cellSize.y) / texture->getHeight() };
    return createRef<SubTexture2D>(texture, min, max);
}
}