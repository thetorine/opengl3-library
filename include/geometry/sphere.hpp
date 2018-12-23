#pragma once

#include <memory>

#include "geometry/shape.hpp"

namespace geometry {
    class Mesh;

    class Sphere : public Shape {
    public:
        Sphere(float radius);
        ~Sphere();
        void draw(const glm::mat4 &model);
    private:
        std::unique_ptr<Mesh> m_sphereMesh;
    };
}