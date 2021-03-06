#include <string>

#include "engine/shader_controller.hpp"
#include "illumination/spotlight.hpp"

namespace gl::illumination {

    Spotlight::Spotlight(const glm::vec3 &pos, const glm::vec3 &dir, const glm::vec3 &color,
                         float intensity, float innerCutoff, float outerCutoff,
                         float attenPow, float attenDist)
        : m_pos(pos),
        m_dir(dir),
        m_color(color),
        m_intensity(intensity),
        m_innerCutoff(innerCutoff),
        m_outerCutoff(outerCutoff),
        m_attenPow(attenPow),
        m_attenDist(attenDist) {
    }

    Spotlight::~Spotlight() {

    }

    void Spotlight::setShaderParams(int index) {
        char buffer[14];
        snprintf(buffer, sizeof(buffer), "spotlights[%d]", index);
        std::string structName { buffer };

        engine::ShaderController::getInstance()->setVec3(structName + ".pos", m_pos);
        engine::ShaderController::getInstance()->setVec3(structName + ".dir", m_dir);
        engine::ShaderController::getInstance()->setVec3(structName + ".color", m_color);
        engine::ShaderController::getInstance()->setFloat(structName + ".intensity", m_intensity);
        engine::ShaderController::getInstance()->setFloat(structName + ".innerCutoff", m_innerCutoff);
        engine::ShaderController::getInstance()->setFloat(structName + ".outerCutoff", m_outerCutoff);
        engine::ShaderController::getInstance()->setFloat(structName + ".attenPow", m_attenPow);
        engine::ShaderController::getInstance()->setFloat(structName + ".attenDist", m_attenDist);
        engine::ShaderController::getInstance()->setInt(structName + ".on", true);
    }

    void Spotlight::setFacingFrom(const glm::vec3 &pos, const glm::vec3 &dir) {
        m_pos = pos;
        m_dir = dir;
    }
}