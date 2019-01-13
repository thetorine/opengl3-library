#pragma once

#include <functional>
#include <utility>
#include <vector>

// needs vertices, indices and normals

namespace gl::math {
    std::vector<float> generateVertices(std::function<float(float t)> fx,
                                        std::function<float(float t)> fy,
                                        std::pair<float, float> bounds,
                                        float sampleRate);
    std::vector<int> generateIndices(std::vector<float> vertices,
                                     std::pair<float, float> bounds,
                                     float sampleRate);
}