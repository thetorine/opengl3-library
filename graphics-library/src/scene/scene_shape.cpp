#include "geometry/line.hpp"
#include "math/matrix.hpp"
#include "scene/scene_shape.hpp"

namespace gl::scene {

    std::shared_ptr<SceneShape> SceneShape::create(const std::shared_ptr<geometry::Shape> &shape) {
        return std::shared_ptr<SceneShape>(new SceneShape(shape));
    }

    SceneShape::SceneShape(const std::shared_ptr<geometry::Shape> &shape)
        : m_shape(shape) {
    }

    void SceneShape::drawSelf() const {
        glm::mat4 globalModel { getGlobalModel() };
        glm::vec3 globalTranslation { gl::math::getTranslationFromMat4(globalModel) };

        // Draw the object stored in this scene object
        m_shape->draw(getGlobalModel());

        // Draw a line to the parent to easily visualise the scene tree
        if (m_parent != nullptr) {
            glm::mat4 parentModel { m_parent->getGlobalModel() };
            glm::vec3 parentTranslation { gl::math::getTranslationFromMat4(parentModel) };

            geometry::Line line(parentTranslation, globalTranslation);
            line.draw();
        }
    }
}