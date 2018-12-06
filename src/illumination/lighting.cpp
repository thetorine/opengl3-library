#include "illumination/Lighting.hpp"
#include "engine/shader.hpp"

#include <stdio.h>

namespace illumination {

    Lighting::Lighting() {
    }

    Lighting::~Lighting() {

    }

    void Lighting::addPointLight(glm::vec3 pos, glm::vec3 color, float intensity) {
        m_pointLights.push_back(PointLight(pos, color, intensity));
    }

    void Lighting::addDirectionalLight(glm::vec3 direction, glm::vec3 color, float intensity) {
        m_directionalLights.push_back(DirectionalLight(direction, color, intensity));
    }

    void Lighting::setShaderType(int type) {
        engine::Shader::getInstance()->setInt("shaderType", type);
    }

    void Lighting::updateShader() {
        for (int i = 0; i < m_pointLights.size(); i++) {
            char buffer[16];
            snprintf(buffer, sizeof(buffer), "pointLights[%d]", i);
            std::string structName = buffer;

            engine::Shader::getInstance()->setVec3(structName + ".pos", m_pointLights[i].getPos());
            engine::Shader::getInstance()->setVec3(structName + ".color", m_pointLights[i].getColor());
            engine::Shader::getInstance()->setFloat(structName + ".intensity", m_pointLights[i].getIntensity());
            engine::Shader::getInstance()->setInt(structName + ".on", true);
        }

        for (int i = 0; i < m_directionalLights.size(); i++) {
            char buffer[22];
            snprintf(buffer, sizeof(buffer), "directionalLights[%d]", i);
            std::string structName = buffer;

            engine::Shader::getInstance()->setVec3(structName + ".dir", m_directionalLights[i].getDir());
            engine::Shader::getInstance()->setVec3(structName + ".color", m_directionalLights[i].getColor());
            engine::Shader::getInstance()->setFloat(structName + ".intensity", m_directionalLights[i].getIntensity());
            engine::Shader::getInstance()->setInt(structName + ".on", true);
        }
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