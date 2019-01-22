#include <limits>

#include <catch.hpp>
#include <glm/glm.hpp>

#include "math/epsilon.hpp"
#include "math/functions.hpp"

const float FLOAT_EPSILON { 1.0e-5f };

TEST_CASE("Epsilon", "[Math]") {
    SECTION("Vec3") {
        glm::vec3 a(0.2f, 0.0f, 0.0f);
        glm::vec3 b(0.2f, 0.1f, 0.0f);

        SECTION("Check equality") {
            REQUIRE(gl::math::epsilonEquals(a, a, FLOAT_EPSILON));
        }

        SECTION("Check inequality") {
            REQUIRE(gl::math::epsilonEquals(a, b, FLOAT_EPSILON) == false);
        }

        SECTION("Check inverse inequality") {
            REQUIRE(gl::math::epsilonEquals(a, -a, FLOAT_EPSILON) == false);
        }
    }

    SECTION("Quat") {
        glm::quat a(glm::vec3(1.0f));
        glm::quat b(glm::vec3(1.1f));

        SECTION("Check equality") {
            REQUIRE(gl::math::epsilonEquals(a, a, FLOAT_EPSILON));
        }

        SECTION("Check inequality") {
            REQUIRE(gl::math::epsilonEquals(a, b, FLOAT_EPSILON) == false);
        }

        SECTION("Check inverse inequality") {
            REQUIRE(gl::math::epsilonEquals(a, -a, FLOAT_EPSILON));
        }
    }

    SECTION("Mat4") {
        glm::mat4 a(1.0f);
        glm::mat4 b(1.1f);

        SECTION("Check equality") {
            REQUIRE(gl::math::epsilonEquals(a, a, FLOAT_EPSILON));
        }

        SECTION("Check inequality") {
            REQUIRE(gl::math::epsilonEquals(a, b, FLOAT_EPSILON) == false);
        }

        SECTION("Check inverse inequality") {
            REQUIRE(gl::math::epsilonEquals(a, a, FLOAT_EPSILON));
        }
    }
}

TEST_CASE("Binomial Coefficient", "[Math]") {
    int c = gl::math::binomialCoeff(0, 0);
    REQUIRE(c == 1);

    c = gl::math::binomialCoeff(1, 0);
    REQUIRE(c == 1);

    c = gl::math::binomialCoeff(1, 1);
    REQUIRE(c == 1);

    c = gl::math::binomialCoeff(4, 0);
    REQUIRE(c == 1);

    c = gl::math::binomialCoeff(4, 4);
    REQUIRE(c == 1);

    c = gl::math::binomialCoeff(4, 2);
    REQUIRE(c == 6);

    c = gl::math::binomialCoeff(30, 15);
    REQUIRE(c == 155117520);
}