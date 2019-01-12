#pragma once

#include <memory>

#include "camera.hpp"
#include "application/application.hpp"
#include "illumination/lighting.hpp"

#include "geometry/line.hpp"
#include "geometry/point.hpp"
#include "geometry/sphere.hpp"
#include "geometry/square.hpp"

namespace gl::app {
    class GeometryTest : public Application {
    public:
        GeometryTest();
        ~GeometryTest();
        void initialize();
        void render();
        void update(float dt);
        void updateView();
    private:
        engine::Camera m_camera;
        illumination::Lighting m_lighting;

        std::unique_ptr<geometry::Line> m_geomLine;
        std::unique_ptr<geometry::Point> m_geomPoint;
        std::unique_ptr<geometry::Sphere> m_geomSphere;
        std::unique_ptr<geometry::Square> m_geomSquare;

        void keyHandler(int key, int action);
    };
}