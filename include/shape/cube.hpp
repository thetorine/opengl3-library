#pragma once

#include <glm/gtc/matrix_transform.hpp>

#include "shape/shape.hpp"
#include "shape/square.hpp"

class cube : public shape
{
public:
	cube();
	~cube();
	void draw(glm::mat4 model);
private:
	square square;

	const glm::mat4 i = glm::mat4(1.0f);
	const glm::mat4 m1 =
		glm::translate(i, glm::vec3(0.0f, 0.0f, 1.0f)) *
		glm::rotate(i, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	const glm::mat4 m2 =
		glm::translate(i, glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::rotate(i, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	const glm::mat4 m3 =
		glm::translate(i, glm::vec3(1.0f, 0.0f, 1.0f)) *
		glm::rotate(i, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	const glm::mat4 m4 =
		glm::translate(i, glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(i, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	const glm::mat4 m5 =
		glm::translate(i, glm::vec3(0.0f, 0.0f, 1.0f)) *
		glm::rotate(i, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
};