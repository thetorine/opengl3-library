#pragma once

#include <glm/glm.hpp>

#include "illumination/light_type.hpp"

namespace illumination {
    class PointLight: public LightType {
    public:
        PointLight(const glm::vec3 &pos, const glm::vec3 &color, float intensity);
        ~PointLight();
        void setShaderParams(int index);
    private:
        glm::vec3 m_pos;
        glm::vec3 m_color;
        float m_intensity;
    };
}