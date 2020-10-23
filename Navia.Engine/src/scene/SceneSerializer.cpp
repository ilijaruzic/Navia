#include "navia/scene/Components.hpp"
#include "navia/scene/Entity.hpp"
#include "navia/scene/SceneSerializer.hpp"
#include <yaml-cpp/yaml.h>

namespace YAML {
template<>
struct convert<glm::vec3> {
    static Node encode(const glm::vec3& vector) {
        Node node;
        node.push_back(vector.x);
        node.push_back(vector.y);
        node.push_back(vector.z);
        return node;
    }

    static bool decode(const Node& node, glm::vec3& vector) {
        if (!node.IsSequence() || node.size() != 3) {
            return false;
        }
        vector.x = node[0].as<float>();
        vector.y = node[1].as<float>();
        vector.z = node[2].as<float>();
        return true;
    }
};

template<>
struct convert<glm::vec4> {
    static Node encode(const glm::vec4& vector) {
        Node node;
        node.push_back(vector.x);
        node.push_back(vector.y);
        node.push_back(vector.z);
        node.push_back(vector.w);
        return node;
    }

    static bool decode(const Node& node, glm::vec4& vector) {
        if (!node.IsSequence() || node.size() != 4) {
            return false;
        }
        vector.x = node[0].as<float>();
        vector.y = node[1].as<float>();
        vector.z = node[2].as<float>();
        vector.w = node[3].as<float>();
        return true;
    }
};
}

namespace Navia {
YAML::Emitter& operator<<(YAML::Emitter& emitter, glm::vec3& vector) {
    emitter << YAML::Flow;
    emitter << YAML::BeginSeq << vector.x << vector.y << vector.z << YAML::EndSeq;
    return emitter;
}

YAML::Emitter& operator<<(YAML::Emitter& emitter, glm::vec4& vector) {
    emitter << YAML::Flow;
    emitter << YAML::BeginSeq << vector.x << vector.y << vector.z << vector.w << YAML::EndSeq;
    return emitter;
}

static void serializeEntity(YAML::Emitter& emitter, Entity entity) {
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "Entity" << YAML::Value << UINT64_MAX;
    if (entity.hasComponent<TagComponent>()) {
        emitter << YAML::Key << "TagComponent";
        emitter << YAML::BeginMap;
        auto& tag = entity.getComponent<TagComponent>();
        emitter << YAML::Key << "Tag" << YAML::Value << tag.tag;
        emitter << YAML::EndMap;
    }
    if (entity.hasComponent<TransformComponent>()) {
        emitter << YAML::Key << "TransformComponent";
        emitter << YAML::BeginMap;
        auto& transform = entity.getComponent<TransformComponent>();
        emitter << YAML::Key << "Translation" << YAML::Value << transform.translation;
        emitter << YAML::Key << "Rotation" << YAML::Value << transform.rotation;
        emitter << YAML::Key << "Scale" << YAML::Value << transform.scale;
        emitter << YAML::EndMap;
    }
    if (entity.hasComponent<CameraComponent>()) {
        emitter << YAML::Key << "CameraComponent";
        emitter << YAML::BeginMap;
        auto& camera = entity.getComponent<CameraComponent>();
        emitter << YAML::Key << "Camera";
        emitter << YAML::BeginMap;
        emitter << YAML::Key << "ProjectionType" << YAML::Value << static_cast<int>(camera.camera.getProjectionType());
        emitter << YAML::Key << "PerspectiveVerticalFOV" << YAML::Value << camera.camera.getPerspectiveVerticalFOV();
        emitter << YAML::Key << "PerspectiveNearClip" << YAML::Value << camera.camera.getPerspectiveNearClip();
        emitter << YAML::Key << "PerspectiveFarClip" << YAML::Value << camera.camera.getPerspectiveFarClip();
        emitter << YAML::Key << "OrthographicSize" << YAML::Value << camera.camera.getOrthographicSize();
        emitter << YAML::Key << "OrthographicNearClip" << YAML::Value << camera.camera.getOrthographicNearClip();
        emitter << YAML::Key << "OrthographicFarClip" << YAML::Value << camera.camera.getOrthographicFarClip();
        emitter << YAML::EndMap;
        emitter << YAML::Key << "Primary" << YAML::Value << camera.primary;
        emitter << YAML::Key << "FixedAspectRatio" << YAML::Value << camera.fixedAspectRatio;
        emitter << YAML::EndMap;
    }
    if (entity.hasComponent<SpriteComponent>()) {
        emitter << YAML::Key << "SpriteComponent";
        emitter << YAML::BeginMap;
        auto& sprite = entity.getComponent<SpriteComponent>();
        emitter << YAML::Key << "Color" << YAML::Value << sprite.color;
        emitter << YAML::EndMap;
    }
    emitter << YAML::EndMap;
}

SceneSerializer::SceneSerializer(Ref<Scene> scene) : scene(scene) {}

void SceneSerializer::serialize(const std::string& filepath, Mode mode) {
    switch (mode) {
        case Mode::Text: {
            serializeToText(filepath);
            break;
        }
        case Mode::Binary: {
            serializeToBinary(filepath);
            break;
        }
    }
    NAVIA_ASSERT(mode == Mode::Text || mode == Mode::Binary, "Unsupported format!");
}

bool SceneSerializer::deserialize(const std::string& filepath, Mode mode) {
    switch (mode) {
        case Mode::Text: {
            return deserializeFromText(filepath);
        }
        case Mode::Binary: {
            return deserializeFromBinary(filepath);
        }
    }
    NAVIA_ASSERT(mode == Mode::Text || mode == Mode::Binary, "Unsupported format!");
    return false;
}

void SceneSerializer::serializeToText(const std::string& filepath) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "Scene" << YAML::Value << "Untitled";
    emitter << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;
    scene->registry.each([&](auto id) {
        Entity entity{ id, scene.get() };
        if (!entity) {
            return;
        }
        serializeEntity(emitter, entity);
    });
    emitter << YAML::EndSeq;
    emitter << YAML::EndMap;

    std::ofstream file{ filepath };
    file << emitter.c_str();
}

void SceneSerializer::serializeToBinary(const std::string& filepath) {
    NAVIA_CORE_ASSERT(false, "Not implemented yet!");
}

bool SceneSerializer::deserializeFromText(const std::string& filepath) {
    std::ifstream file{ filepath };
    std::stringstream content;
    content << file.rdbuf();
    YAML::Node data = YAML::Load(content.str());
    if (!data["Scene"]) {
        return false;
    }
    std::string sceneName = data["Scene"].as<std::string>();
    NAVIA_CORE_TRACE("Deserializing scene '{0}'...", sceneName);
    auto entities = data["Entities"];
    if (entities) {
        for (auto entity : entities) {
            uint64_t entityId = entity["Entity"].as<uint64_t>();
            std::string entityName;
            auto tag = entity["TagComponent"];
            if (tag) {
                entityName = tag["Tag"].as<std::string>();
            }
            NAVIA_CORE_TRACE("Deserializing entity with id={0} and name={1}...", entityId, entityName);
            Entity deserializedEntity = scene->createEntity(entityName);
            auto transform = entity["TransformComponent"];
            if (transform) {
                auto& deserializedTransform = deserializedEntity.getComponent<TransformComponent>();
                deserializedTransform.translation = transform["Translation"].as<glm::vec3>();
                deserializedTransform.rotation = transform["Rotation"].as<glm::vec3>();
                deserializedTransform.scale = transform["Scale"].as<glm::vec3>();
            }
            auto camera = entity["CameraComponent"];
            if (camera) {
                auto& deserializedCamera = deserializedEntity.addComponent<CameraComponent>();
                auto cameraProperties = camera["Camera"];
                deserializedCamera.camera.setProjectionType(static_cast<SceneCamera::ProjectionType>(cameraProperties["ProjectionType"].as<int>()));
                deserializedCamera.camera.setPerspectiveVerticalFOV(cameraProperties["PerspectiveVerticalFOV"].as<float>());
                deserializedCamera.camera.setPerspectiveNearClip(cameraProperties["PerspectiveNearClip"].as<float>());
                deserializedCamera.camera.setPerspectiveFarClip(cameraProperties["PerspectiveFarClip"].as<float>());
                deserializedCamera.camera.setOrthographicSize(cameraProperties["OrthographicSize"].as<float>());
                deserializedCamera.camera.setOrthographicNearClip(cameraProperties["OrthographicNearClip"].as<float>());
                deserializedCamera.camera.setOrthographicFarClip(cameraProperties["OrthographicFarClip"].as<float>());
                deserializedCamera.primary = camera["Primary"].as<bool>();
                deserializedCamera.fixedAspectRatio = camera["FixedAspectRatio"].as<bool>();
            }
            auto sprite = entity["SpriteComponent"];
            if (sprite) {
                auto& deserializedSprite = deserializedEntity.addComponent<SpriteComponent>();
                deserializedSprite.color = sprite["Color"].as<glm::vec4>();
            }
        }
    }
    return true;
}

bool SceneSerializer::deserializeFromBinary(const std::string& filepa) {
    NAVIA_CORE_ASSERT(false, "Not implemented yet!");
    return false;
}
}