#include "utilities.hpp"

#include <stdio.h>

#include <fstream>
#include <sstream>

namespace engine {

    GLuint genVAO() {
        GLuint vertexArrayID;
        glGenVertexArrays(1, &vertexArrayID);
        glBindVertexArray(vertexArrayID);
        return vertexArrayID;
    }

    GLuint bufferData(const void *data, int size, GLuint mode) {
        GLuint bufferID;
        glGenBuffers(1, &bufferID);
        glBindBuffer(mode, bufferID);
        glBufferData(mode, size, data, GL_STATIC_DRAW);
        return bufferID;
    }

    std::string readFile(std::string file) {
        std::ifstream t(file);
        std::stringstream buffer;
        buffer << t.rdbuf();
        return buffer.str();
    }
}