#include "lighting/point_light.hpp"

point_light::point_light(glm::vec3 pos, glm::vec3 color, float intensity)
	: pos(pos), color(color), intensity(intensity)
{}

point_light::~point_light() {

}

glm::vec3 point_light::getPos() {
	return pos;
}

glm::vec3 point_light::getColor() {
	return color;
}

float point_light::getIntensity() {
	return intensity;
}