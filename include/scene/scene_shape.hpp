#pragma once

#include "geometry/shape.hpp"
#include "scene/scene_object.hpp"

namespace gl::scene {
    class SceneShape : public SceneObject {
    public:
        static std::shared_ptr<SceneShape> create(const std::shared_ptr<geometry::Shape> &shape);
        void drawSelf() const;
    private:
        std::shared_ptr<geometry::Shape> m_shape;
        SceneShape(const std::shared_ptr<geometry::Shape> &shape);
    };
}