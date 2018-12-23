#include <fstream>
#include <sstream>

#include "utilities.hpp"

namespace engine {

    GLuint genVAO() {
        GLuint vertexArrayID;
        glGenVertexArrays(1, &vertexArrayID);
        glBindVertexArray(vertexArrayID);
        return vertexArrayID;
    }

    std::string readFile(std::string file) {
        std::ifstream t(file);
        std::stringstream buffer;
        buffer << t.rdbuf();
        return buffer.str();
    }

    bool epsilonEquals(const glm::vec3 &a, const glm::vec3 &b, float epsilon) {
        return std::abs(a.x - b.x) <= epsilon &&
            std::abs(a.y - b.y) <= epsilon &&
            std::abs(a.z - b.z) <= epsilon;
    }
}