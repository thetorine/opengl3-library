#pragma once

#include <string>
#include <GL/glew.h>

namespace gl::engine {
    GLuint genVAO();
    std::string readFile(std::string file);
}