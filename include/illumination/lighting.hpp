#pragma once

#include <memory>
#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "illumination/directional_light.hpp"
#include "illumination/point_light.hpp"

#define PHONG_SHADER 0
#define CEL_SHADER 1

namespace illumination {
    class Lighting {
    public:
        Lighting();
        ~Lighting();

        void addPointLight(glm::vec3 pos, glm::vec3 color, float intensity);
        void addDirectionalLight(glm::vec3 direction, glm::vec3 color, float intensity);

        void updateShader();

        void setShaderType(int type);
        void setMaterialCoeffs(float ambient, float diffuse, float specular, float phongExp);
        void setMaterialIntensities(glm::vec3 ambient, glm::vec3 diffuse);
    private:
        std::vector<PointLight> m_pointLights;
        std::vector<DirectionalLight> m_directionalLights;
    };
}