#pragma once

#include <memory>

#include "camera.hpp"
#include "application/application.hpp"
#include "geometry/mesh.hpp"
#include "illumination/lighting.hpp"

namespace app {
    class Test : public Application {
    public:
        Test();
        ~Test();
        void initialize();
        void render();
        void update(float dt);
        void updateView();
    private:
        engine::Camera m_camera;
        illumination::Lighting m_lighting;

        std::unique_ptr<geometry::Mesh> m_model;

        void keyHandler(int key, int action);
    };
}