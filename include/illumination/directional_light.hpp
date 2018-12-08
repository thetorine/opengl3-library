#pragma once

#include <glm/glm.hpp>

#include "illumination/light_type.hpp"

namespace illumination {
    class DirectionalLight: public LightType {
    public:
        DirectionalLight(glm::vec3 dir, glm::vec3 color, float intensity);
        ~DirectionalLight();
        void setShaderParams(int index);
    private:
        glm::vec3 m_dir;
        glm::vec3 m_color;
        float m_intensity;
    };
}