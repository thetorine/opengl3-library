#pragma once

#include <functional>
#include <vector>

#include <glm/glm.hpp>

// should be able to define the number of control points for a single bezier curve - call this n
// the total number of control points passed will satisfy the condition TOTAL_POINTS % n == 0
// all points greater than n will form a bezier spline. 
// should be able to get a function to pass into revolution.hpp
// should be able to form a bezier curve/spline from either 2d or 3d points. 

namespace gl::math {
    class Bezier {
    public:
        Bezier(int order);
        Bezier(int order, const std::vector<glm::vec3> &controlPoints);

        ~Bezier();

        void insertPoints(const std::vector<glm::vec3> &controlPoints);

        std::function<float(float t)> getX() const;
        std::function<float(float t)> getY() const;
        std::function<float(float t)> getZ() const;
        float getT() const;
    private:
        float p(float t, int pointIndex) const;
        float bernstein(int k, float t) const;

        int m_degree;
        std::vector<glm::vec3> m_controlPoints;
    };
}