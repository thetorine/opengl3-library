#pragma once

#include "geometry/shape.hpp"

namespace geometry {
	class Square : public Shape {
	public:
		Square();
		~Square();
		void draw(glm::mat4 &model);
	private:
		uint32_t m_vertexBuffer;
		uint32_t m_normalBuffer;
		uint32_t m_uvBuffer;

		const float m_vertices[18] = {
			0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			1.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f,
			1.0f, 1.0f, 0.0f,
			1.0f, 0.0f, 0.0f
		};
		const float m_normals[18] = {
			0.0f, 0.0f, -1.0f,
			0.0f, 0.0f, -1.0f,
			0.0f, 0.0f, -1.0f,
			0.0f, 0.0f, -1.0f,
			0.0f, 0.0f, -1.0f,
			0.0f, 0.0f, -1.0f
		};
		const float m_uv[12] = {
			0.0f, 0.0f,
			0.0f, 1.0f,
			1.0f, 1.0f,
			0.0f, 0.0f,
			1.0f, 1.0f,
			1.0f, 0.0f
		};
	};
}