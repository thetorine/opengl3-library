#include <vector>

#include "geometry/sphere.hpp"
#include "utilities.hpp"

namespace geometry {

    Sphere::Sphere(float radius) {
        static const float pi = static_cast<float>(std::acos(-1));

        float sampleRate = 0.1f;
        int pointCount = static_cast<int>(std::ceil(2.0f * pi / sampleRate));

        std::vector<float> vertices;
        std::vector<float> normals;
        std::vector<int> indices;

        for (float yTheta = 0.0f; yTheta <= pi; yTheta += sampleRate) {
            float xzR = radius * std::sin(yTheta);
            float y = radius * std::cos(yTheta);

            for (float xzTheta = 0.0f; xzTheta <= 2 * pi; xzTheta += sampleRate) {
                float x = xzR * std::cos(xzTheta);
                float z = xzR * std::sin(xzTheta);

                glm::vec3 n = glm::normalize(glm::vec3(x, y, z));

                vertices.insert(std::end(vertices), { x, y, z });
                normals.insert(std::end(normals), { n.x, n.y, n.z });

                int count = static_cast<int>(vertices.size() / 3);
                if (count > pointCount) {
                    indices.insert(std::end(indices),
                        { count - 1, count - 2, count - pointCount });
                    indices.insert(std::end(indices),
                        { count - 1, count - pointCount, count - pointCount + 1 });
                }
            }
        }

        m_sphereMesh = std::make_unique<Mesh>(vertices, normals, indices);
    }

    Sphere::~Sphere() {

    }

    void Sphere::draw(glm::mat4 &model) {
        m_sphereMesh->draw(model);
    }
}