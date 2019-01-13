#pragma once

#include <memory>
#include <vector>

#include <glm/glm.hpp>

namespace gl::illumination {
    class LightType;
    class PointLight;
    class DirectionalLight;
    class Spotlight;

    const int SHADER_COUNT = 3;

    class Lighting {
    public:
        Lighting();
        ~Lighting();

        void addPointLight(const std::shared_ptr<PointLight> &pointLight);
        void addDirectionalLight(const std::shared_ptr<DirectionalLight> &directionalLight);
        void addSpotlight(const std::shared_ptr<Spotlight> &spotlight);

        void updateShader();

        void nextShaderType();
        void setMaterialCoeffs(float ambient, float diffuse, float specular, float phongExp);
        void setMaterialIntensities(const glm::vec3 &ambient, const glm::vec3 &diffuse);
    private:
        std::vector<std::shared_ptr<LightType>> m_directionalLights;
        std::vector<std::shared_ptr<LightType>> m_pointLights;
        std::vector<std::shared_ptr<LightType>> m_spotlights;
        int m_currentShader = 0;
    };
}