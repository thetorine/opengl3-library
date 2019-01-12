#include "engine/shader.hpp"
#include "illumination/point_light.hpp"

namespace gl::illumination {

    PointLight::PointLight(const glm::vec3 &pos, const glm::vec3 &color, float intensity)
        : m_pos(pos), m_color(color), m_intensity(intensity) {
    }

    PointLight::~PointLight() {

    }

    void PointLight::setShaderParams(int index) {
        char buffer[16];
        snprintf(buffer, sizeof(buffer), "pointLights[%d]", index);
        std::string structName { buffer };

        engine::Shader::getInstance()->setVec3(structName + ".pos", m_pos);
        engine::Shader::getInstance()->setVec3(structName + ".color", m_color);
        engine::Shader::getInstance()->setFloat(structName + ".intensity", m_intensity);
        engine::Shader::getInstance()->setInt(structName + ".on", true);
    }

}