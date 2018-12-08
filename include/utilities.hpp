#pragma once

#include <string>
#include <GL/glew.h>

namespace engine {
    GLuint genVAO();
    std::string readFile(std::string file);
}