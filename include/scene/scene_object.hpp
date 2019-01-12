#pragma once

#include <memory>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace gl::scene {
    class SceneObject : public std::enable_shared_from_this<SceneObject> {
    public:
        static std::shared_ptr<SceneObject> create();
        ~SceneObject();

        void setParent(const std::shared_ptr<SceneObject> &parent);
        void addChild(const std::shared_ptr<SceneObject> &child);
        void removeChild(const std::shared_ptr<SceneObject> &child);

        void draw() const;
        virtual void drawSelf() const;

        void update(float dt);
        virtual void updateSelf(float dt);

        void reparent(const std::shared_ptr<SceneObject> &newParent);

        void translate(const glm::vec3 &dm);
        void rotate(const glm::vec3 &dr);
        void scale(const glm::vec3 &ds);

        void setTranslation(const glm::vec3 &dm);
        void setRotation(const glm::vec3 &dr);
        void setScale(const glm::vec3 &ds);

        glm::mat4 getModel() const;
        const glm::vec3 &getTranslation() const;
        const glm::quat &getRotation() const;
        const glm::vec3 &getScale() const;

        glm::mat4 getGlobalModel() const;

        size_t getSize() const;
        const std::shared_ptr<SceneObject> &getParent() const;
    protected:
        SceneObject();

        std::shared_ptr<SceneObject> m_parent;
        std::vector<std::shared_ptr<SceneObject>> m_children;
        glm::vec3 m_translation;
        glm::quat m_rotation;
        glm::vec3 m_scale;
    private:
    };
}