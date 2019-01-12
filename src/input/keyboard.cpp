#include <map>
#include <mutex>
#include <cstdio>

#include "input/events.hpp"
#include "input/keyboard.hpp"

namespace gl::input {

    std::map<int, bool> keyMapping;
    std::mutex keyMutex;

    void glfwKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
        // TODO: A way to make this better would be to abstract the key and action so that it
        // is separated from GLFW once it reaches the event handler. 
        onKeyPress(key, action);
    }
}