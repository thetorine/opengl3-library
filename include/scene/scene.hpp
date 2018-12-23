#pragma once

#include "scene/scene_object.hpp"

namespace scene {
    class Scene {
    public:
        Scene();
        ~Scene();

        void reparent(SceneObject &obj, SceneObject &originalParent, SceneObject &newParent);
    };
}