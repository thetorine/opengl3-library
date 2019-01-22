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
        return (static_cast<float>(m_controlPoints.size()) - 1.0f) /
                static_cast<float>(m_degree);
    }

    // https://en.wikipedia.org/wiki/B%C3%A9zier_curve
    float Bezier::p(float t, int pointIndex) const {
        /*
            All Bezier curves are interpolated with the parameter t in the range [0, 1].
            A Bezier Spline can formed by interpolating from the last point of the previous curve
            to the first point of the next curve. 

            For example if we have the control points P0, P1, P2, P3, P4, we can form two
            Bezier curves to create a Bezier Spline.

            The first Bezier curve will be interpolated from P0 to P2.
            The second Bezier curve will be interpolated from P2 to P4.

            This function assumes that if t is in the range [0, 1], then the first curve is
            getting interpolated. 
            But if t is in the range [1, 2], then the second curve is getting interpolated.

            t is the current interpolation value. 
            pointIndex is the dimension that is being interpolated, 0 = x, 1 = y and 2 = z.
        */

        // The index of the current curve to interpolate.
        float tFloor = std::floorf(t);
        // The starting point of the curve. 
        int base { static_cast<int>(tFloor * m_degree) };
        // Each curve must be interpolated between [0, 1].
        float tNorm { t - tFloor };

        // If the base is negative, return the first point in the spline. 
        if (base < 0) {
            return m_controlPoints[0][pointIndex];
        }

        // If the base + the degree of the curve exceeds the number of points,
        // return the last point in the spline.
        if (m_degree + base >= m_controlPoints.size()) {
            return m_controlPoints[base][pointIndex];
        }

        float p { 0 };
        for (int k { 0 }; k <= m_degree; k++) {
            // Calculate the Bezier curve.
            // Base is appended to k, so that the correct curve is getting drawn
            // based on the current value of t.
            p += bernstein(k, tNorm) * m_controlPoints[k + base][pointIndex];
        }
        return p;
    }

    // https://en.wikipedia.org/wiki/Bernstein_polynomial
    float Bezier::bernstein(int k, float t) const {
        return binomialCoeff(m_degree, k) *
            std::powf(t, static_cast<float>(k)) *
            std::powf(1.0 - t, static_cast<float>(m_degree - k));
    }
}