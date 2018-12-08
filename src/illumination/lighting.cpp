#include <algorithm>

#include "engine/shader.hpp"
#include "illumination/lighting.hpp"
#include "illumination/directional_light.hpp"
#include "illumination/point_light.hpp"
#include "illumination/spotlight.hpp"

namespace illumination {

    Lighting::Lighting() {
    }

    Lighting::~Lighting() {

    }

    void Lighting::addPointLight(glm::vec3 pos, glm::vec3 color, float intensity) {
        m_pointLights.push_back(std::make_shared<PointLight>(pos, color, intensity));
    }

    void Lighting::addDirectionalLight(glm::vec3 direction, glm::vec3 color, float intensity) {
        m_directionalLights.push_back(std::make_shared<DirectionalLight>(direction, color, intensity));
    }

    void Lighting::addSpotlight(std::shared_ptr<Spotlight> spotlight) {
        m_spotlights.push_back(spotlight);
    }

    void Lighting::nextShaderType() {
        m_currentShader = (m_currentShader + 1) % SHADER_COUNT;
        engine::Shader::getInstance()->setInt("shaderType", m_currentShader);
    }

    void Lighting::updateShader() {
        auto setShaderParams = [index = 0](std::shared_ptr<LightType> &value) mutable {
            value->setShaderParams(index++);
        };

        std::for_each(m_pointLights.begin(), m_pointLights.end(), setShaderParams);
        std::for_each(m_directionalLights.begin(), m_directionalLights.end(), setShaderParams);
        std::for_each(m_spotlights.begin(), m_spotlights.end(), setShaderParams);
    }

    void Lighting::setMaterialCoeffs(float ambient, float diffuse, float specular, float phongExp) {
        engine::Shader::getInstance()->setFloat("ambientCoeff", ambient);
        engine::Shader::getInstance()->setFloat("diffuseCoeff", diffuse);
        engine::Shader::getInstance()->setFloat("specularCoeff", specular);
        engine::Shader::getInstance()->setFloat("phongExp", phongExp);
    }

    void Lighting::setMaterialIntensities(glm::vec3 ambient, glm::vec3 diffuse) {
        engine::Shader::getInstance()->setVec3("ambientIntensity", ambient);
        engine::Shader::getInstance()->setVec3("diffuseIntensity", diffuse);
    }
}