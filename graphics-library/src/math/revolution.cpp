#include <cmath>

#include "math/constants.hpp"
#include "math/revolution.hpp"

namespace gl::math {
    // Wraps negative numbers around to d
    int wrap(int n, int d) {
        if (n >= 0) return n;
        return d + n;
    }

    /*
        If the curve (fx(t), fy(t)) where t is in the range [bounds.first, bounds.second] is rotated,
        about the y axis, the result will be a 3D curve. 
                   y
                   ^    z 
                   |   /
                   |*****  
                   | /  *
                   |/   *
        <----------|----------->x
                  /|    *
                 / |    *
                /  |*****
               /   |
                   v
        Rotating the curve specified by the asterisks(*) on the x and y axis around the y axis will form
        a cylinder.
    */
    std::vector<float> generateVertices(std::function<float(float t)> fx,
                                        std::function<float(float t)> fy,
                                        std::pair<float, float> bounds,
                                        float sampleRate) {
        std::vector<float> vertices;

        int n { static_cast<int>(bounds.second / sampleRate - bounds.first / sampleRate) };

        // Take a 2d curve in the first and fourth quadrant and rotate it around the y axis
        // to generate a 3d curve.
        for (float theta { 0.0f }; theta <= gl::math::PI * 2.0f; theta += sampleRate) {
            float tx { std::cos(theta) };
            float tz { std::sin(theta) };
            // Use integers to avoid floating point errors.
            // This ensures that a constant number of points are generated per ring.
            // Hence it is easier to generate indices later on.
            for (int i { 0 }; i <= n; i++) {
                float t { bounds.first + i * sampleRate };
                float x { fx(t) * tx };
                float y { fy(t) };
                float z { fx(t) * tz };
                vertices.insert(std::end(vertices), { x, y, z });
            }
        }

        return vertices;
    }

    std::vector<int> generateIndices(std::vector<float> vertices,
                                     std::pair<float, float> bounds,
                                     float sampleRate) {
        std::vector<int> indices;

        // Basic algorithm: Create triangles between the current and previous ring.
        // Since there are a constant number of points on each ring, we can subtract that constant number
        // from the current vertex to retrieve the index of the adjacent vertex. 
        // Then the indexes need to be wrapped to avoid negative indices. 

        // The number of points on each ring if a curve in quadrants 1 and 4 is swept around the y axis. 
        int n { static_cast<int>(bounds.second / sampleRate - bounds.first / sampleRate) + 1};
        // Every three elements forms one vertex (x, y, z) and indices map to each vertex. 
        int vertexCount = static_cast<int>(vertices.size() / size_t(3));
        for (int i { 0 }; i < vertexCount; i++) {
            // Creates the following face:
            /*
                o-o
                |/
                o o
            */
            indices.insert(std::end(indices), 
                           {i, wrap(i - n, vertexCount), wrap(i - n + 1, vertexCount) });

            // Creates the following face:
            /*
                o-o
                 /|                   
                o-o
            */
            indices.insert(std::end(indices),
                           {i, wrap(i - 1, vertexCount), wrap(i - n, vertexCount) });
        }

        return indices;
    }
}