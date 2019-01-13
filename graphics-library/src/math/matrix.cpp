#include <glm/gtx/quaternion.hpp>

#include "math/matrix.hpp"

namespace gl::math {

    void decomposeMat4(const glm::mat4 &mat,
                       glm::vec3 &translation,
                       glm::quat &rotation,
                       glm::vec3 &scale) {
        translation = getTranslationFromMat4(mat);
        rotation = getRotationFromMat4(mat);
        scale = getScaleFromMat4(mat);
    }

    glm::vec3 getTranslationFromMat4(const glm::mat4 &mat) {
        // The translation vector in an affine transformation matrix is the 4th column.
        /*
        | a b c x |
        | d e f y |
        | g h i z |
        | 0 0 0 1 |
        */
        return static_cast<glm::vec3>(mat[3]);
    }

    glm::quat getRotationFromMat4(const glm::mat4 &mat) {
        // Extract the rotation matrix from the global matrix and then
        // use quat_cast to get the quaternion.

        glm::vec4 i { mat[0] };
        glm::vec4 j { mat[1] };
        glm::vec4 k { mat[2] };

        glm::vec3 scale = getScaleFromMat4(mat);

        glm::mat4 rotationMatrix { glm::mat4(
            i / scale[0],
            j / scale[1],
            k / scale[2],
            glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
        ) };

        return glm::quat_cast(rotationMatrix);
    }

    glm::vec3 getScaleFromMat4(const glm::mat4 &mat) {
        glm::vec4 i { mat[0] };
        glm::vec4 j { mat[1] };
        glm::vec4 k { mat[2] };

        // The scale of each axis in an affine transformation matrix is the
        // length of each axis vector. 
        return glm::vec3(
            glm::length(i),
            glm::length(j),
            glm::length(k)
        );
    }
}