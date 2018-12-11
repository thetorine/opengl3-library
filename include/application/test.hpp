#pragma once

#include "application/application.hpp"

namespace app {
    class Test : public Application {
    public:
        Test();
        ~Test();
        void initialize();
        void render();
        void update(float dt);
    };
}