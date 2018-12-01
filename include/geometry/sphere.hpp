#pragma once

#include "geometry/shape.hpp"
#include "buffer.hpp"

class sphere : public shape
{
public:
	sphere(float radius);
	~sphere();
	void draw(glm::mat4 model);
private:
	buffer<float> vertexBuffer = buffer<float>(GL_ARRAY_BUFFER);
	buffer<int> indexBuffer = buffer<int>(GL_ELEMENT_ARRAY_BUFFER);
	buffer<float> normalBuffer = buffer<float>(GL_ARRAY_BUFFER);
};