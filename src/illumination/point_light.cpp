#include "illumination/point_light.hpp"

namespace illumination {

	PointLight::PointLight(glm::vec3 pos, glm::vec3 color, float intensity)
		: m_pos(pos), m_color(color), m_intensity(intensity)
	{}

	PointLight::~PointLight() {

	}

	glm::vec3 PointLight::getPos() {
		return m_pos;
	}

	glm::vec3 PointLight::getColor() {
		return m_color;
	}

	float PointLight::getIntensity() {
		return m_intensity;
	}
}