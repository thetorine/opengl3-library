#include <glm/glm.hpp>

#include "illumination/light_type.hpp"

namespace illumination {
    class Spotlight : public LightType {
    public:
        Spotlight(glm::vec3 pos, glm::vec3 dir, glm::vec3 color, float intensity, float cutoff);
        ~Spotlight();
        void setShaderParams(int index);
        void setFacingFrom(glm::vec3 pos, glm::vec3 dir);
    private:
        glm::vec3 m_pos;
        glm::vec3 m_dir;
        glm::vec3 m_color;
        float m_intensity;
        float m_cutoff;
    };
}