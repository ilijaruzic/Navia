#ifndef _SCENE_SERIALIZER_HPP_
#define _SCENE_SERIALIZER_HPP_

#include "navia/core/Base.hpp"
#include "navia/scene/Scene.hpp"

namespace Navia {
class SceneSerializer {
public:
    enum class Mode { Text, Binary };

    SceneSerializer(Ref<Scene> scene);

    void serialize(const std::string& filepath, Mode mode = Mode::Text);
    bool deserialize(const std::string& filepath, Mode mode = Mode::Text);

private:
    Ref<Scene> scene;

    void serializeToText(const std::string& filepath);
    void serializeToBinary(const std::string& filepath);
    bool deserializeFromText(const std::string& filepath);
    bool deserializeFromBinary(const std::string& filepath);
};
}

#endif