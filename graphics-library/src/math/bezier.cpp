#include "math/bezier.hpp"
#include "math/functions.hpp"

namespace gl::math {
    Bezier::Bezier(int order)
        : Bezier(order, std::vector<glm::vec3>()) {
    }

    Bezier::Bezier(int order, const std::vector<glm::vec3> &controlPoints)
        : m_degree(order - 1), m_controlPoints(controlPoints) {
    }

    Bezier::~Bezier() {}

    void Bezier::insertPoints(const std::vector<glm::vec3> &controlPoints) {
        m_controlPoints.insert(std::end(m_controlPoints), 
                               std::begin(controlPoints), std::end(controlPoints));
    }

    std::function<float(float t)> Bezier::getX() const {
        return [this](float t) -> float {
            return p(t, 0);
        };
    }

    std::function<float(float t)> Bezier::getY() const {
        return [this](float t) -> float {
            return p(t, 1);
        };
    }

    std::function<float(float t)> Bezier::getZ() const {
        return [this](float t) -> float {
            return p(t, 2);
        };
    }

    float Bezier::getT() const {
        return static_cast<float>(m_controlPoints.size()) / static_cast<float>(m_degree + 1);
    }

    float Bezier::p(float t, int pointIndex) const {
        float p { 0 };
        for (int k { 0 }; k <= m_degree; k++) {
            p += bernstein(k, t) * m_controlPoints[k][pointIndex];
        }
        return p;
    }

    float Bezier::bernstein(int k, float t) const {
        // (n k) * t^k * (1 - t)^(n-k)
        return binomialCoeff(m_degree, k) *
            std::powf(t, static_cast<float>(k)) *
            std::powf(1.0 - t, static_cast<float>(m_degree - k));
    }
}