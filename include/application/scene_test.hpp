#pragma once

#include <memory>
#include <vector>

#include "camera.hpp"
#include "application/application.hpp"
#include "geometry/point.hpp"
#include "illumination/lighting.hpp"
#include "scene/scene.hpp"
#include "scene/scene_shape.hpp"

namespace gl::app {
    class SceneTest : public Application {
    public:
        SceneTest();
        ~SceneTest();
        void initialize();
        void render();
        void update(float dt);
        void updateView();
    private:
        engine::Camera m_camera;
        illumination::Lighting m_lighting;
        scene::Scene m_scene;

        std::unique_ptr<geometry::Point> m_lightSource;
        std::vector<std::shared_ptr<scene::SceneObject>> m_sceneObjects;

        std::shared_ptr<scene::SceneShape> m_parentObj;
        std::shared_ptr<scene::SceneShape> m_child1Obj;
        std::shared_ptr<scene::SceneShape> m_child2Obj;
        std::shared_ptr<scene::SceneShape> m_grandchild1Obj;
        std::shared_ptr<scene::SceneShape> m_reparentObj;
        float m_child1Rotation;
        float m_grandchild1Rotation;
        float m_grandchild2Rotation;

        int m_currentParent;

        void keyHandler(int key, int action);
    };
}