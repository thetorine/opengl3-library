#pragma once

#include <memory>
#include <vector>

#include "geometry/mesh.hpp"

namespace gl::geometry {
    class Square : public Shape {
    public:
        Square();
        ~Square();
        void draw(const glm::mat4 &model = glm::mat4(1.0f));
    private:
        Mesh m_squareMesh;
    };
}