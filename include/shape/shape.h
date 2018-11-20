#pragma once

#include <glm/glm.hpp>

class shape
{
public:
	virtual ~shape() = default;
	virtual void draw(glm::mat4 model) = 0;
};

