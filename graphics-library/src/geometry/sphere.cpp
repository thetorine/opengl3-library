#include <functional>
#include <vector>

#include "geometry/mesh.hpp"
#include "geometry/sphere.hpp"
#include "math/constants.hpp"
#include "math/revolution.hpp"

namespace gl::geometry {

    Sphere::Sphere(float radius) {
        std::function<float(float)> fx = [radius](float t) { return radius * std::sin(t); };
        std::function<float(float)> fy = [radius](float t) { return radius * std::cos(t); };
        std::pair<float, float> bounds = std::make_pair<float, float>(0.0f, gl::math::PI * 1.0f);

        std::vector<float> vertices { gl::math::generateVertices(fx, fy, bounds, 0.1f) };
        std::vector<int> indices { gl::math::generateIndices(vertices, bounds, 0.1f) };

        // For a sphere, normals are the same as the vertices.
        m_sphereMesh = std::make_unique<Mesh>(vertices, vertices, indices);
    }

    Sphere::~Sphere() {

    }

    void Sphere::draw(const glm::mat4 &model) {
        m_sphereMesh->draw(model);
    }
}