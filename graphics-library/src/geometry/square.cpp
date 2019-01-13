#include "geometry/mesh.hpp"
#include "geometry/square.hpp"

namespace gl::geometry {

    std::vector<float> squareVertices {
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
    };

    std::vector<float> squareNormals {
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
    };

    std::vector<int> squareIndices {
        2, 1, 0,
        2, 0, 3
    };

    Square::Square()
        : m_squareMesh(squareVertices, squareNormals, squareIndices) {
    }

    Square::~Square() {

    }

    void Square::draw(const glm::mat4 &model) {
        m_squareMesh.draw(model);
    }
}