#pragma once

#include <glm/glm.hpp>

namespace illumination {
    class PointLight {
    public:
        PointLight(glm::vec3 pos, glm::vec3 color, float intensity);
        ~PointLight();

        glm::vec3 getPos();
        glm::vec3 getColor();
        float getIntensity();
    private:
        glm::vec3 m_pos;
        glm::vec3 m_color;
        float m_intensity;
    };
}