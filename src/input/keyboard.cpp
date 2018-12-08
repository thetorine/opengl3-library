#include <map>

#include "input/keyboard.hpp"

namespace input {

    std::map<int, bool> keyMapping;

    void glfwKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
        keyMapping[key] = [key, action]() {
            if (action == GLFW_PRESS) {
                return true;
            } else if (action == GLFW_RELEASE) {
                return false;
            } else {
                return isPressed(key);
            }
        }();
    }

    bool isPressed(int key) {
        if (keyMapping.find(key) == keyMapping.end()) {
            return false;
        }
        return keyMapping[key];
    }

    bool wasPressed(int key) {
        bool pressed = isPressed(key);
        if (pressed) {
            keyMapping[key] = false;
        }
        return pressed;
    }
}