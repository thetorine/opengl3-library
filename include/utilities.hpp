#pragma once

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace engine {
    GLuint genVAO();
    std::string readFile(std::string file);
    bool epsilonEquals(const glm::vec3 &a, const glm::vec3 &b, float epsilon);
}