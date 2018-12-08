#pragma once

#include <memory>
#include <vector>

#include <glm/glm.hpp>

namespace illumination {
    class LightType;
    class Spotlight;

    const int SHADER_COUNT = 3;

    class Lighting {
    public:
        Lighting();
        ~Lighting();

        void addPointLight(glm::vec3 pos, glm::vec3 color, float intensity);
        void addDirectionalLight(glm::vec3 direction, glm::vec3 color, float intensity);
        void addSpotlight(std::shared_ptr<Spotlight> spotlight);

        void updateShader();

        void nextShaderType();
        void setMaterialCoeffs(float ambient, float diffuse, float specular, float phongExp);
        void setMaterialIntensities(glm::vec3 ambient, glm::vec3 diffuse);
    private:
        std::vector<std::shared_ptr<LightType>> m_directionalLights;
        std::vector<std::shared_ptr<LightType>> m_pointLights;
        std::vector<std::shared_ptr<LightType>> m_spotlights;
        int m_currentShader = 0;
    };
}