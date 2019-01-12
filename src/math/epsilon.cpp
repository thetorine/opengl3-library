#include "math/epsilon.hpp"
#include <cstdio>
namespace gl::math {
    bool epsilonEquals(const glm::vec3 &a, const glm::vec3 &b, float epsilon) {
        return std::abs(a.x - b.x) <= epsilon &&
            std::abs(a.y - b.y) <= epsilon &&
            std::abs(a.z - b.z) <= epsilon;
    }

    bool epsilonEquals(const glm::quat &a, const glm::quat &b, float epsilon) {
        bool check = std::abs(a.x - b.x) <= epsilon &&
            std::abs(a.y - b.y) <= epsilon &&
            std::abs(a.z - b.z) <= epsilon &&
            std::abs(a.w - b.w) <= epsilon;
        bool conjugateCheck = std::abs(a.x + b.x) <= epsilon &&
            std::abs(a.y + b.y) <= epsilon &&
            std::abs(a.z + b.z) <= epsilon &&
            std::abs(a.w + b.w) <= epsilon;
        return check || conjugateCheck;
    }

    bool epsilonEquals(const glm::mat4 &a, const glm::mat4 &b, float epsilon) {
        for (int x { 0 }; x < 4; x++) {
            for (int y { 0 }; y < 4; y++) {
                if (std::abs(a[x][y] - b[x][y]) > epsilon) {
                    return false;
                }
            }
        }
        return true;
    }
}