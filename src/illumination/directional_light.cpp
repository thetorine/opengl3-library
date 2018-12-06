#include "illumination/directional_light.hpp"

namespace illumination {

	DirectionalLight::DirectionalLight(glm::vec3 dir, glm::vec3 color, float intensity)
		: m_dir(dir), m_color(color), m_intensity(intensity)
	{}

	DirectionalLight::~DirectionalLight() {

	}

	glm::vec3 DirectionalLight::getDir() {
		return m_dir;
	}

	glm::vec3 DirectionalLight::getColor() {
		return m_color;
	}

	float DirectionalLight::getIntensity() {
		return m_intensity;
	}
}