#pragma once

#include <glm/glm.hpp>

namespace gl::geometry {
    class Shape {
    public:
        virtual ~Shape() = default;
        virtual void draw(const glm::mat4 &model = glm::mat4(1.0f)) = 0;
    };
}
