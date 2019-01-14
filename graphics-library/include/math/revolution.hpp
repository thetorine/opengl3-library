#pragma once

#include <functional>
#include <utility>
#include <vector>

// needs vertices, indices and normals

namespace gl::math {
    std::vector<float> generateVertices(const std::function<float(float t)> &fx,
                                        const std::function<float(float t)> &fy,
                                        const std::pair<float, float> &bounds,
                                        float sampleRate);
    std::vector<int> generateIndices(const std::vector<float> &vertices,
                                     const std::pair<float, float> &bounds,
                                     float sampleRate);
    std::vector<float> generateNormals(const std::vector<float> &vertices,
                                       const std::vector<int> &indices);
}