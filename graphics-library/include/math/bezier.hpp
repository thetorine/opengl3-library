#pragma once

#include <functional>
#include <vector>

#include <glm/glm.hpp>

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