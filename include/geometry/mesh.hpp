#pragma once

#include <string>
#include <vector>

#include "buffer.hpp"
#include "geometry/shape.hpp"

class mesh : public shape
{
public:
	mesh(std::string file);
	mesh(std::vector<float> &vertices, std::vector<float> &normals, std::vector<int> &indices);
	~mesh();
	void draw(glm::mat4 &model);
private:
	buffer<float> vertexBuffer = buffer<float>(GL_ARRAY_BUFFER);
	buffer<float> normalBuffer = buffer<float>(GL_ARRAY_BUFFER);
	buffer<int> indexBuffer = buffer<int>(GL_ELEMENT_ARRAY_BUFFER);

	bool hasIndices;
};