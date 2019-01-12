#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace gl::math {

    void decomposeMat4(const glm::mat4 &mat,
                       glm::vec3 &translation,
                       glm::quat &rotation,
                       glm::vec3 &scale);
    glm::vec3 getTranslationFromMat4(const glm::mat4 &mat);
    glm::quat getRotationFromMat4(const glm::mat4 &mat);
    glm::vec3 getScaleFromMat4(const glm::mat4 &mat);
}