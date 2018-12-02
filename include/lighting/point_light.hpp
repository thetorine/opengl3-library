#pragma once

#include <glm/glm.hpp>

class point_light {
public:
	point_light(glm::vec3 pos, glm::vec3 color, float intensity);
	~point_light();

	glm::vec3 getPos();
	glm::vec3 getColor();
	float getIntensity();
private:
	glm::vec3 pos;
	glm::vec3 color;
	float intensity;
};