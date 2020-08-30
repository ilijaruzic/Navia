#ifndef _SCRIPTABLE_ENTITY_HPP_
#define _SCRIPTABLE_ENTITY_HPP_

#include "navia/scene/Entity.hpp"

namespace Navia {
class ScriptableEntity {
public:
    virtual ~ScriptableEntity() = default;

    template <typename Component>
    Component& getComponent() {
        return entity.getComponent<Component>();
    }

protected:
    virtual void onCreate();
    virtual void onUpdate(Timestep timestep);
    virtual void onDestroy();

private:
    Entity entity;

    friend class Scene;
};
}

#endif