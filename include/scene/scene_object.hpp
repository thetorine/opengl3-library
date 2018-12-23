#pragma once

#include <memory>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "geometry/shape.hpp"

namespace scene {
    class SceneObject {
    public:
        SceneObject();
        ~SceneObject();

        void addChild(std::shared_ptr<SceneObject> child);
        
        void draw(const glm::mat4 &parentMatrix);

        void move(const glm::vec3 &dm);
        void rotate(const glm::vec3 &dr);
        void scale(const glm::vec3 &ds);

        glm::mat4 getModel() const;
        const glm::vec3 &getTranslation() const;
        const glm::quat &getRotation() const;
        const glm::vec3 &getScale() const;

        glm::mat4 getGlobalModel(const glm::mat4 &parentMatrix) const;
        glm::vec3 getGlobalTranslation(const glm::mat4 &parentMatrix) const;
        glm::quat getGlobalRotation(const glm::mat4 &parentMatrix) const;
        glm::vec3 getGlobalScale(const glm::mat4 &parentMatrix) const;
    private:
        std::vector<std::shared_ptr<SceneObject>> m_children;
        glm::vec3 m_translation;
        glm::quat m_rotation;
        glm::vec3 m_scale;
    };
}