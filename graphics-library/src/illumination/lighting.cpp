#include <algorithm>

#include "engine/shader_controller.hpp"
#include "illumination/lighting.hpp"
#include "illumination/directional_light.hpp"
#include "illumination/point_light.hpp"
#include "illumination/spotlight.hpp"

namespace gl::illumination {

    Lighting::Lighting() {
    }

    Lighting::~Lighting() {

    }

    void Lighting::addPointLight(const std::shared_ptr<PointLight> &pointLight) {
        m_pointLights.push_back(pointLight);
    }

    void Lighting::addDirectionalLight(const std::shared_ptr<DirectionalLight> &directionalLight) {
        m_directionalLights.push_back(directionalLight);
    }

    void Lighting::addSpotlight(const std::shared_ptr<Spotlight> &spotlight) {
        m_spotlights.push_back(spotlight);
    }

    void Lighting::nextShaderType() {
        m_currentShader = (m_currentShader + 1) % SHADER_COUNT;
        engine::ShaderController::getInstance()->setInt("shaderType", m_currentShader);
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
        engine::ShaderController::getInstance()->setFloat("ambientCoeff", ambient);
        engine::ShaderController::getInstance()->setFloat("diffuseCoeff", diffuse);
        engine::ShaderController::getInstance()->setFloat("specularCoeff", specular);
        engine::ShaderController::getInstance()->setFloat("phongExp", phongExp);
    }

    // TODO: Add the ability to change the specular light color. 
    void Lighting::setMaterialIntensities(const glm::vec3 &ambient, const glm::vec3 &diffuse) {
        engine::ShaderController::getInstance()->setVec3("ambientIntensity", ambient);
        engine::ShaderController::getInstance()->setVec3("diffuseIntensity", diffuse);
    }
}