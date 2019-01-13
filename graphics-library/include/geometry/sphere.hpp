#pragma once

#include <memory>

#include "geometry/shape.hpp"

namespace gl::geometry {
    class Mesh;

    class Sphere : public Shape {
    public:
        Sphere(float radius);
        ~Sphere();
        void draw(const glm::mat4 &model = glm::mat4(1.0f));
    private:
        std::unique_ptr<Mesh> m_sphereMesh;
    };
}