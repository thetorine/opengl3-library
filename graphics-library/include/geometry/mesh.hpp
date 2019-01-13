#pragma once

#include <memory>
#include <string>
#include <vector>

#include "engine/buffer.hpp"
#include "geometry/shape.hpp"

namespace gl::geometry {
    class Mesh : public Shape {
    public:
        Mesh(std::string file);
        Mesh(const std::vector<float> &vertices, const std::vector<float> &normals, const std::vector<int> &indices);
        ~Mesh();
        void draw(const glm::mat4 &model = glm::mat4(1.0f));
    private:
        engine::Buffer<float> m_vertexBuffer;
        engine::Buffer<float> m_normalBuffer;
        engine::Buffer<int> m_indexBuffer;
        engine::Buffer<float> m_colorBuffer;

        bool m_hasIndices;
    };
}