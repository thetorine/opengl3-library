#include "shape/cube.hpp"
#include "shader.hpp"
#include "utilities.hpp"

cube::cube() {
}

cube::~cube() {
}

void cube::draw(glm::mat4 model) {
	setModelMatrix(model);

	square.draw(i);
	square.draw(m1);
	square.draw(m2);
	square.draw(m3);
	square.draw(m4);
	square.draw(m5);
}