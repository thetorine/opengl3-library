#pragma once

#include <glm/glm.hpp>

namespace geometry {
    class Shape {
    public:
        virtual ~Shape() = default;
        virtual void draw(const glm::mat4 &model) = 0;
    };
}
