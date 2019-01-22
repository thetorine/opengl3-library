#pragma once

#include <functional>
#include <utility>
#include <vector>

// this could be a class..

namespace gl::math {
    std::vector<float> generateVertices(const std::function<float(float t)> &fx,
                                        const std::function<float(float t)> &fy,
                                        const std::pair<float, float> &bounds,
                                        bool rotate = true);
    std::vector<float> generateNormals(const std::function<float(float t)> &fx,
                                        const std::function<float(float t)> &fy,
                                        const std::pair<float, float> &bounds);
    std::vector<int> generateIndices(const std::vector<float> &vertices,
                                     const std::pair<float, float> &bounds);

    std::vector<float> generateNormals_broken(const std::vector<float> &vertices,
                                       const std::vector<int> &indices);
}