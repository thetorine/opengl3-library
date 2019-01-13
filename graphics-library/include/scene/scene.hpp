#pragma once

#include <vector>

#include "scene/scene_object.hpp"

namespace gl::scene {
    class Scene {
    public:
        Scene();
        ~Scene();

        void addChild(const std::shared_ptr<SceneObject> &child);
        void drawScene() const;
        void updateScene(float dt);
        size_t getTreeSize() const;
    private:
        std::vector<std::shared_ptr<SceneObject>> m_root;
    };
}