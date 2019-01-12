#include <fstream>
#include <sstream>

#include "utilities.hpp"

namespace gl::engine {

    GLuint genVAO() {
        GLuint vertexArrayID;
        glGenVertexArrays(1, &vertexArrayID);
        glBindVertexArray(vertexArrayID);
        return vertexArrayID;
    }

    std::string readFile(std::string file) {
        std::ifstream t { file };
        std::stringstream buffer;
        buffer << t.rdbuf();
        return buffer.str();
    }
}