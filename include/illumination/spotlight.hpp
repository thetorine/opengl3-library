#include <glm/glm.hpp>

#include "illumination/light_type.hpp"

namespace gl::illumination {
    class Spotlight : public LightType {
    public:
        Spotlight(const glm::vec3 &pos, const glm::vec3 &dir, const glm::vec3 &color,
                  float intensity, float innerCutoff, float outerCutoff,
                  float attenPow, float attenDist);
        ~Spotlight();
        void setShaderParams(int index);
        void setFacingFrom(const glm::vec3 &pos, const glm::vec3 &dir);
    private:
        glm::vec3 m_pos;
        glm::vec3 m_dir;
        glm::vec3 m_color;
        float m_intensity;
        float m_innerCutoff;
        float m_outerCutoff;
        float m_attenPow;
        float m_attenDist;
    };
}