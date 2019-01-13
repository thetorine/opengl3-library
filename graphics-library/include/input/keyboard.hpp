#pragma once

#include <GLFW/glfw3.h>

namespace gl::input {
    void glfwKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
}
