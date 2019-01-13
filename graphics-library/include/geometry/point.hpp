#pragma once

#include "engine/buffer.hpp"
#include "geometry/shape.hpp"

namespace gl::geometry {
    class Point : public Shape {
    public:
        Point(const std::vector<float> &vertices);
        ~Point();
        void draw(const glm::mat4 &model = glm::mat4(1.0f));
    private:
        engine::Buffer<float> m_vertexBuffer;
    };
}