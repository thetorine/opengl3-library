#include <algorithm>
#include <cmath>
#include <glm/glm.hpp>

#include "math/constants.hpp"
#include "math/revolution.hpp"

namespace gl::math {
    // Wraps negative numbers around to d
    int wrap(int n, int d) {
        if (n >= 0) return n;
        return d + n;
    }

    // The vertices in the vector are stored in the format (x1, y1, z1, x2, y2, z2, ..., xn, yn, zn)
    // This function will retrieve the xyz coordinates at the specified index and return as a vec3.
    glm::vec3 getVertex(const std::vector<float> &vertices, int vertex) {
        int index { vertex * 3 };
        return glm::vec3(vertices[index], vertices[index + 1], vertices[index + 2]);
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
    std::vector<float> generateVertices(const std::function<float(float t)> &fx,
                                        const std::function<float(float t)> &fy,
                                        const std::pair<float, float> &bounds,
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

    // TODO: There is a bug that is causing a face to be generated between the top and the bottom of the generated mesh.
    // It is breaking the normal generation at the top of the mesh as well.
    std::vector<int> generateIndices(const std::vector<float> &vertices,
                                     const std::pair<float, float> &bounds,
                                     float sampleRate) {
        std::vector<int> indices;

        // Basic algorithm: Create triangles between the current and previous ring.
        // Since there are a constant number of points on each ring, we can subtract that constant number
        // from the current vertex to retrieve the index of the adjacent vertex. 
        // Then the indexes need to be wrapped to avoid negative indices. 

        // The number of points on each ring if a curve in quadrants 1 and 4 is swept around the y axis. 
        int n { static_cast<int>(bounds.second / sampleRate - bounds.first / sampleRate) + 1 };
        // Every three elements forms one vertex (x, y, z) and indices map to each vertex. 
        int vertexCount = static_cast<int>(vertices.size() / static_cast<size_t>(3));
        for (int i { 0 }; i < vertexCount; i++) {
            // Creates the following face:
            /*
                o-o
                |/
                o o
            */
            indices.insert(std::end(indices),
                           { i, wrap(i - n, vertexCount), wrap(i - n + 1, vertexCount) });

            // Creates the following face:
            /*
                o-o
                 /|
                o-o
            */
            indices.insert(std::end(indices),
                           { i, wrap(i - 1, vertexCount), wrap(i - n, vertexCount) });
        }

        return indices;
    }

    std::vector<float> generateNormals(const std::vector<float> &vertices,
                                       const std::vector<int> &indices) {
        // Vertex normals can be calculated by taking the 
        // average of all adjacent face normals. 

        // This vector will sum all the face normals that are adjacent to each vertex. 
        std::vector<glm::vec3> normalSum(vertices.size() / 3);
        // This vector will count the number of face normals that are adjacent to each vertex.
        std::vector<int> faceNormalCount(vertices.size() / 3);

        for (int i { 0 }; i <= indices.size() - 3; i += 3) {
            // Retrieve the indexes to each of the three vertices that make up each face. 
            int v1Index { indices[i] };
            int v2Index { indices[i + 1] };
            int v3Index { indices[i + 2] };

            // Get the vertex xyz coordinates at each vertex index.
            glm::vec3 v1 { getVertex(vertices, v1Index) };
            glm::vec3 v2 { getVertex(vertices, v2Index) };
            glm::vec3 v3 { getVertex(vertices, v3Index) };

            // The face normal is calculated by calculating the cross product
            // of P(i-1) - P(i) and P(i+1) - P(i).
            glm::vec3 i1 { v1 - v2 }; // P(i-1) - P(i)
            glm::vec3 i2 { v3 - v2 }; // P(i+1) - P(i)

            // [P(i-1) - P(i)] X [P(i+1) - P(i)]
            glm::vec3 faceNormal { glm::normalize(glm::cross(i1, i2)) };

            // Add the face normal to the normalSum for each vertex of the face.
            normalSum[v1Index] += faceNormal;
            normalSum[v2Index] += faceNormal;
            normalSum[v3Index] += faceNormal;

            // Increment the counts.
            faceNormalCount[v1Index] += 1;
            faceNormalCount[v2Index] += 1;
            faceNormalCount[v3Index] += 1;
        }

        std::vector<float> result;
        for (int i { 0 }; i < normalSum.size(); i++) {
            // Calculate the vertex normal by calculating the average of the face normals. 
            glm::vec3 normal { normalSum[i] / static_cast<float>(faceNormalCount[i]) };
            result.insert(std::end(result), { normal.x, normal.y, normal.z });
        }

        return result;
    }
}