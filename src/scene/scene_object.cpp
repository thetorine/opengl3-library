#include <algorithm>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include "math/matrix.hpp"
#include "scene/scene_object.hpp"

namespace gl::scene {

    std::shared_ptr<SceneObject> SceneObject::create() {
        return std::shared_ptr<SceneObject>(new SceneObject());
    }

    SceneObject::SceneObject()
        : m_translation(glm::vec3(0.0f)),
        m_rotation(glm::vec3(0.0f)),
        m_scale(glm::vec3(1.0f)) {
    }

    SceneObject::~SceneObject() {}

    void SceneObject::setParent(const std::shared_ptr<SceneObject> &parent) {
        m_parent = parent;
    }

    void SceneObject::addChild(const std::shared_ptr<SceneObject> &child) {
        m_children.push_back(child);
        child->setParent(shared_from_this());
    }

    void SceneObject::removeChild(const std::shared_ptr<SceneObject> &child) {
        m_children.erase(std::remove(std::begin(m_children), std::end(m_children), child), std::end(m_children));
    }

    void SceneObject::draw() const {
        // Traverse children and then perform draw self
        for (const auto &child : m_children) {
            child->draw();
        }
        drawSelf();
    }

    void SceneObject::drawSelf() const {}

    void SceneObject::update(float dt) {
        for (const auto &child : m_children) {
            child->update(dt);
        }
        updateSelf(dt);
    }

    void SceneObject::updateSelf(float dt) {}

    void SceneObject::reparent(const std::shared_ptr<SceneObject> &newParent) {
        /*
            Let this objects global matrix = gc
            Let this objects local matrix = lc
            Let this objects new local matrix = lcn
            Let the original parents global matrix = go
            Let the new parents global matrix = gn
            Let the new parents inverse global matrix = gn^-1

            Originally:
                gc = go * lc

            When the scene object is reparented, we want its global matrix to
            remain unchanged.

            Hence:
                gc = gn * lcn

            As gc and gn are known, we must determine the value for lcn:
                lcn = gn^-1 * gc
        */

        glm::mat4 gc = getGlobalModel(); // gc
        glm::mat4 inverseGn = glm::inverse(newParent->getGlobalModel()); // gn^-1
        glm::mat4 lcn = inverseGn * gc; // lcn = gn^-1 * gc

        // Decompose the new local matrix into its components
        math::decomposeMat4(lcn, m_translation, m_rotation, m_scale);

        // Update the tree so that the reparenting is correctly reflected. 
        std::shared_ptr<SceneObject> thisSptr = shared_from_this();

        m_parent->removeChild(thisSptr);
        newParent->addChild(thisSptr);
        m_parent = newParent;
    }

    void SceneObject::translate(const glm::vec3 &dm) {
        m_translation += dm;
    }

    void SceneObject::rotate(const glm::vec3 &dr) {
        m_rotation = glm::normalize(glm::quat(dr) * m_rotation);
    }

    void SceneObject::scale(const glm::vec3 &ds) {
        m_scale *= ds;
    }

    void SceneObject::setTranslation(const glm::vec3 &dm) {
        m_translation = dm;
    }

    void SceneObject::setRotation(const glm::vec3 &dr) {
        m_rotation = glm::quat(dr);
    }

    void SceneObject::setScale(const glm::vec3 &ds) {
        m_scale = ds;
    }

    glm::mat4 SceneObject::getModel() const {
        glm::mat4 result {
            glm::translate(glm::mat4(1.0f), m_translation) *
            glm::toMat4(m_rotation) *
            glm::scale(glm::mat4(1.0f), m_scale) };
        return result;
    }

    const glm::vec3 &SceneObject::getTranslation() const {
        return m_translation;
    }

    const glm::quat &SceneObject::getRotation() const {
        return m_rotation;
    }

    const glm::vec3 &SceneObject::getScale() const {
        return m_scale;
    }

    glm::mat4 SceneObject::getGlobalModel() const {
        // Note: Matrix multiplications are read from right to left.
        // The following is the local model matrix multiplied by the global model matrix.
        if (m_parent == nullptr) {
            return getModel();
        }
        return m_parent->getGlobalModel() * getModel();
    }

    size_t SceneObject::getSize() const {
        size_t size = 1;
        for (const auto &child : m_children) {
            size += child->getSize();
        }
        return size;
    }

    const std::shared_ptr<SceneObject> &SceneObject::getParent() const {
        return m_parent;
    }
}
