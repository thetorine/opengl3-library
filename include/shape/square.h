#pragma once

#include "shape/shape.h"

class square : public shape
{
public:
	square();
	~square();
	void draw(glm::mat4 model);
private:
	uint32_t vertexBuffer;
	uint32_t indexBuffer;
	uint32_t uvBuffer;

	const float vertices[12] = {
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f
	};
	const int indices[6] = {
		0, 1, 2,
		0, 2, 3
	};
	const float normals[12] = {
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f
	};
	const float uv[8] = {
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f
	};
};