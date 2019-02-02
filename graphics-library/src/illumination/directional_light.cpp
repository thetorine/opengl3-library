#include <string>

#include "engine/shader_controller.hpp"
#include "illumination/directional_light.hpp"

namespace gl::illumination {

    DirectionalLight::DirectionalLight(const glm::vec3 &dir, const glm::vec3 &color, float intensity)
        : m_dir(dir), m_color(color), m_intensity(intensity) {
    }

    DirectionalLight::~DirectionalLight() {

    }

    void DirectionalLight::setShaderParams(int index) {
        char buffer[22];
        snprintf(buffer, sizeof(buffer), "directionalLights[%d]", index);
        std::string structName { buffer };

        engine::ShaderController::getInstance()->setVec3(structName + ".dir", m_dir);
        engine::ShaderController::getInstance()->setVec3(structName + ".color", m_color);
        engine::ShaderController::getInstance()->setFloat(structName + ".intensity", m_intensity);
        engine::ShaderController::getInstance()->setInt(structName + ".on", true);
    }
}