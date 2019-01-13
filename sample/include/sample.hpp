#pragma once

#include <memory>
#include <vector>

#include "camera.hpp"
#include "application/application.hpp"
#include "illumination/lighting.hpp"
#include "scene/scene.hpp"
#include "scene/scene_shape.hpp"

class Sample : public gl::app::Application {
public:
    Sample();
    ~Sample();
    void initialize();
    void render();
    void update(float dt);
    void updateView();
private:
    gl::engine::Camera m_camera;
    gl::illumination::Lighting m_lighting;
    gl::scene::Scene m_scene;

    std::vector<std::shared_ptr<gl::scene::SceneObject>> m_sceneObjects;

    std::shared_ptr<gl::scene::SceneShape> m_parentObj;
    std::shared_ptr<gl::scene::SceneShape> m_child1Obj;
    std::shared_ptr<gl::scene::SceneShape> m_child2Obj;
    std::shared_ptr<gl::scene::SceneShape> m_grandchild1Obj;
    std::shared_ptr<gl::scene::SceneShape> m_reparentObj;
    float m_child1Rotation;
    float m_grandchild1Rotation;
    float m_grandchild2Rotation;

    int m_currentParent;

    void keyHandler(int key, int action);
};