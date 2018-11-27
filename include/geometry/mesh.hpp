#pragma once

#include <string>

#include "geometry/shape.hpp"

class mesh : public shape
{
public:
	mesh(std::string file);
	~mesh();
	void draw(glm::mat4 model);
private:
	int vertexCount;
	uint32_t vertexBuffer;
	uint32_t normalBuffer;
	uint32_t indexBuffer;
};