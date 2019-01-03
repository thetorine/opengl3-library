#pragma once

#include <memory>
#include <string>
#include <tuple>
#include <vector>

#include "engine/buffer.hpp"
#include "geometry/shape.hpp"

namespace geometry {
    class Mesh : public Shape {
    public:
        Mesh(std::string file);
        Mesh(const std::vector<float> &vertices, const std::vector<float> &normals, const std::vector<int> &indices);
        ~Mesh();
        void draw(const glm::mat4 &model);
    private:
        engine::Buffer<float> m_vertexBuffer;
        engine::Buffer<float> m_normalBuffer;
        engine::Buffer<int> m_indexBuffer;
        engine::Buffer<float> m_colorBuffer;

        bool m_hasIndices;
    };
}