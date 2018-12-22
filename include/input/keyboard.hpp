#pragma once

#include <GLFW/glfw3.h>

namespace input {
    void glfwKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
}
