#pragma once

#include "geometry/shape.hpp"

class sphere : public shape
{
public:
	sphere(float radius);
	~sphere();
	void draw(glm::mat4 model);
private:
	uint32_t vertexBuffer;
	uint32_t indexBuffer;
	uint32_t normalBuffer;

	uint32_t vertexCount;
	uint32_t indexCount;
	uint32_t normalCount;
};