#include <string>

#include "engine/shader.hpp"
#include "illumination/spotlight.hpp"

namespace illumination {

    Spotlight::Spotlight(glm::vec3 pos, glm::vec3 dir, glm::vec3 color, 
        float intensity, float cutoff, float attenPow) 
        : m_pos(pos),
          m_dir(dir),
          m_color(color),
          m_intensity(intensity),
          m_cutoff(cutoff),
          m_attenPow(attenPow)
    {}

    Spotlight::~Spotlight() {

    }

    void Spotlight::setShaderParams(int index) {
        char buffer[14];
        snprintf(buffer, sizeof(buffer), "spotlights[%d]", index);
        std::string structName = buffer;

        engine::Shader::getInstance()->setVec3(structName + ".pos", m_pos);
        engine::Shader::getInstance()->setVec3(structName + ".dir", m_dir);
        engine::Shader::getInstance()->setVec3(structName + ".color", m_color);
        engine::Shader::getInstance()->setFloat(structName + ".intensity", m_intensity);
        engine::Shader::getInstance()->setFloat(structName + ".cutoff", m_cutoff);
        engine::Shader::getInstance()->setFloat(structName + ".attenPow", m_attenPow);
        engine::Shader::getInstance()->setInt(structName + ".on", true);
    }

    void Spotlight::setFacingFrom(glm::vec3 pos, glm::vec3 dir) {
        m_pos = pos;
        m_dir = dir;
    }
}