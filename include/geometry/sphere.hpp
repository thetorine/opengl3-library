#pragma once

#include <memory>

#include "geometry/shape.hpp"
#include "geometry/mesh.hpp"
#include "buffer.hpp"

class sphere : public shape
{
public:
	sphere(float radius);
	~sphere();
	void draw(glm::mat4 &model);
private:
	std::unique_ptr<mesh> sphereMesh;
};