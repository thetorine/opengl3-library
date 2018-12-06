#pragma once

#include <glm/glm.hpp>

namespace illumination {
	class DirectionalLight {
	public:
		DirectionalLight(glm::vec3 dir, glm::vec3 color, float intensity);
		~DirectionalLight();

		glm::vec3 getDir();
		glm::vec3 getColor();
		float getIntensity();
	private:
		glm::vec3 m_dir;
		glm::vec3 m_color;
		float m_intensity;
	};
}