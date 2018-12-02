#pragma once

#include <memory>
#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "shader.hpp"
#include "lighting/point_light.hpp"

class lighting {
public:
	lighting();
	~lighting();

	void addPointLight(glm::vec3 pos, glm::vec3 color, float intensity);
	void addDirectionalLight(glm::vec3 direction, glm::vec3 color, float intensity);

	void updateShader();

	void setMaterialCoeffs(float ambient, float diffuse, float specular, float phongExp);
	void setMaterialIntensities(glm::vec3 ambient, glm::vec3 diffuse);
private:
	std::vector<point_light> pointLightList;
};