#include "input/events.hpp"
#include "input/mouse.hpp"

namespace gl::input {

    void glfwMouseCallback(GLFWwindow *window, double xPos, double yPos) {
        int width, height;
        glfwGetWindowSize(window, &width, &height);

        // Assuming that the mouse is centered in the screen, dx and dy
        // are calculated by calculating the difference in the coordinates
        // from the center.

        // If the x position is on the left of the center, then the difference
        // returned will be negative and positive otherwise.
        // If the y position is above the center, then the difference
        // returned will be negative and positive otherwise. 

        float dx { static_cast<float>(xPos - width / 2) };
        float dy { static_cast<float>(yPos - height / 2) };

        int focused = glfwGetWindowAttrib(window, GLFW_FOCUSED);
        if (focused) {
            onCursorMove(dx, dy);
        }
    }
}