#pragma once

#include <memory>
#include <vector>

#include "geometry/shape.hpp"

namespace geometry {
    class Mesh;

    class Square : public Shape {
    public:
        Square();
        ~Square();
        void draw(glm::mat4 &model);
    private:
        std::unique_ptr<Mesh> m_squareMesh;
    };
}