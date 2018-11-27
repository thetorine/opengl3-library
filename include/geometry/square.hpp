#pragma once

#include "geometry/shape.hpp"

class square : public shape
{
public:
	square();
	~square();
	void draw(glm::mat4 model);
private:
	uint32_t vertexBuffer;
	uint32_t normalBuffer;
	uint32_t uvBuffer;

	const float vertices[18] = {
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f
	};
	const float normals[18] = {
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f
	};
	const float uv[12] = {
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 0.0f
	};
};