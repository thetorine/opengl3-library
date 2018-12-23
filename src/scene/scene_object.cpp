#include <glm/gtc/matrix_transform.hpp>

#include "scene/scene_object.hpp"

namespace scene {

    SceneObject::SceneObject() 
        : m_translation(glm::vec3(0.0f)),
          m_rotation(glm::vec3(0.0f)),
          m_scale(glm::vec3(1.0f))
    {}

    SceneObject::~SceneObject() {}

    void SceneObject::addChild(std::shared_ptr<SceneObject> child) {
        m_children.push_back(child);
    }

    void SceneObject::move(const glm::vec3 &dm) {
        m_translation += dm;
    }

    void SceneObject::rotate(const glm::vec3 &dr) {
        m_rotation = glm::normalize(glm::quat(dr) * m_rotation);
    }

    void SceneObject::scale(const glm::vec3 &ds) {
        m_scale *= ds;
    }

    glm::mat4 SceneObject::getModel() const {
        glm::mat4 result =
            glm::translate(glm::mat4(1.0f), m_translation) *
            glm::toMat4(m_rotation) *
            glm::scale(glm::mat4(1.0f), m_scale);
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

    glm::mat4 SceneObject::getGlobalModel(const glm::mat4 &parentMatrix) const {
        // Note: Matrix multiplications are read from right to left.
        // The following is the local model matrix multiplied by the global model matrix. 
        return parentMatrix * getModel();
    }

    glm::vec3 SceneObject::getGlobalTranslation(const glm::mat4 &parentMatrix) const {
        glm::mat4 globalMatrix = getGlobalModel(parentMatrix);
        // The translation vector in an affine transformation matrix is the 4th column.
        /*
           | a b c x |
           | d e f y |
           | g h i z |
           | 0 0 0 1 |
        
        */
        return static_cast<glm::vec3>(globalMatrix[3]);
    }

    glm::quat SceneObject::getGlobalRotation(const glm::mat4 &parentMatrix) const {
        // Extract the rotation matrix from the global matrix and then
        // use quat_cast to get the quaternion.
        // TODO: GLM might have a function to decompose an affine transformation matrix
        // into translation, rotation and scale matrices. 
        glm::mat4 globalMatrix = getGlobalModel(parentMatrix);
        glm::vec3 globalScale = getGlobalScale(parentMatrix);
        glm::mat4 rotationMatrix = glm::mat4(
            globalMatrix[0] / globalScale[0],
            globalMatrix[1] / globalScale[1],
            globalMatrix[2] / globalScale[2],
            glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
        );

        return glm::quat_cast(rotationMatrix);
    }

    glm::vec3 SceneObject::getGlobalScale(const glm::mat4 &parentMatrix) const {
        glm::mat4 globalMatrix = getGlobalModel(parentMatrix);

        glm::vec3 i = static_cast<glm::vec3>(globalMatrix[0]);
        glm::vec3 j = static_cast<glm::vec3>(globalMatrix[1]);
        glm::vec3 k = static_cast<glm::vec3>(globalMatrix[2]);

        // The scale of each axis in an affine transformation matrix is the
        // length of each axis vector. 
        return glm::vec3(
            glm::length(i),
            glm::length(j),
            glm::length(k)
        );
    }
}