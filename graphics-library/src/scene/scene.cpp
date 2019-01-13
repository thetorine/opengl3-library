#include "scene/scene.hpp"

namespace gl::scene {

    Scene::Scene() {

    }

    Scene::~Scene() {

    }

    void Scene::addChild(const std::shared_ptr<SceneObject> &child) {
        m_root.push_back(child);
    }

    void Scene::drawScene() const {
        for (const auto &child : m_root) {
            child->draw();
        }
    }

    void Scene::updateScene(float dt) {
        for (const auto &child : m_root) {
            child->update(dt);
        }
    }

    size_t Scene::getTreeSize() const {
        size_t size = 0;
        for (const auto &child : m_root) {
            size += child->getSize();
        }
        return size;
    }
}