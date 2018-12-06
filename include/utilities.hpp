#pragma once

#include <string>
#include <GL/glew.h>

namespace engine {
    GLuint genVAO();
    GLuint bufferData(const void *data, int size, GLuint mode);
    std::string readFile(std::string file);
}