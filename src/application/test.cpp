#include "application/test.hpp"

namespace app {

    Test::Test() 
        : Application::Application("Test", 1280, 720)
    {
    }

    Test::~Test() {

    }

    void Test::initialize() {

    }

    void Test::render() {
        if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            destroy();

        std::printf("rendering\n");
    }

    void Test::update(float dt) {
        std::printf("%f\n", dt);
    }
}