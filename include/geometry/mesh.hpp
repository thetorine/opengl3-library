#pragma once

#include <memory>
#include <string>
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
        std::unique_ptr<engine::Buffer<float>> m_vertexBuffer;
        std::unique_ptr<engine::Buffer<float>> m_normalBuffer;
        std::unique_ptr<engine::Buffer<int>> m_indexBuffer;

        bool m_hasIndices;
    };
}