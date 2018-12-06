#pragma once

#include <memory>
#include <string>
#include <vector>
#include <glm/glm.hpp>

namespace illumination {
    class DirectionalLight;
    class PointLight;

    const int SHADER_COUNT = 3;

    class Lighting {
    public:
        Lighting();
        ~Lighting();

        void addPointLight(glm::vec3 pos, glm::vec3 color, float intensity);
        void addDirectionalLight(glm::vec3 direction, glm::vec3 color, float intensity);

        void updateShader();

        void nextShaderType();
        void setMaterialCoeffs(float ambient, float diffuse, float specular, float phongExp);
        void setMaterialIntensities(glm::vec3 ambient, glm::vec3 diffuse);
    private:
        std::vector<PointLight> m_pointLights;
        std::vector<DirectionalLight> m_directionalLights;
        int m_currentShader = 0;
    };
}