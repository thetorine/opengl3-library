#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace gl::math {
    bool epsilonEquals(const glm::vec3 &a, const glm::vec3 &b, float epsilon);
    bool epsilonEquals(const glm::quat &a, const glm::quat &b, float epsilon);
    bool epsilonEquals(const glm::mat4 &a, const glm::mat4 &b, float epsilon);
}