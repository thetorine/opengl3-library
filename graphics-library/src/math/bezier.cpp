#include "math/bezier.hpp"
#include "math/functions.hpp"

namespace gl::math {

    Bezier::Bezier(int order)
        : Bezier(order, std::vector<glm::vec3>()) {
    }

    Bezier::Bezier(int order, const std::vector<glm::vec3> &controlPoints)
        : m_order(order), m_controlPoints(controlPoints) {
    }

    Bezier::~Bezier() {}

    void Bezier::insertPoints(const std::vector<glm::vec3> &controlPoints) {
        m_controlPoints.insert(std::end(m_controlPoints), 
                               std::begin(controlPoints), std::end(controlPoints));
    }

    std::function<float(float t)> Bezier::getX() const {

    }

    float Bezier::getT() const {
        return static_cast<float>(m_controlPoints.size()) / static_cast<float>(m_order);
    }

    float Bezier::p(int k, float t) const {
        return 0.0f;
    }

    float Bezier::bernstein(int k, float t) const {
        return binomialCoeff(m_order, k) *
            std::powf(t, static_cast<float>(k)) *
            std::powf(1.0 - t, static_cast<float>(m_order - k));
    }
}