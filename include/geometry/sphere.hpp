#pragma once

#include <memory>

#include "geometry/shape.hpp"
#include "geometry/mesh.hpp"
#include "engine/buffer.hpp"

namespace geometry {
	class Sphere : public Shape {
	public:
		Sphere(float radius);
		~Sphere();
		void draw(glm::mat4 &model);
	private:
		std::unique_ptr<Mesh> m_sphereMesh;
	};
}