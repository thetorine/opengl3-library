#pragma once

#include <string>

#include "buffer.hpp"
#include "geometry/shape.hpp"

class mesh : public shape
{
public:
	mesh(std::string file);
	~mesh();
	void draw(glm::mat4 model);
private:
	buffer<float> vertexBuffer = buffer<float>(GL_ARRAY_BUFFER);
	buffer<float> normalBuffer = buffer<float>(GL_ARRAY_BUFFER);
};