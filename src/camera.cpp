#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "camera.hpp"
#include "input/events.hpp"

namespace engine {

    typedef enum dir {
        FORWARD = 32, RIGHT = 16, BACKWARD = 8, LEFT = 4, UP = 2, DOWN = 1
    } dir_t;

    Camera::Camera(const glm::vec3 &pos, const glm::vec3 &rotation, const glm::vec3 &up)
        : m_pos(pos), m_rotation(rotation), m_up(up) 
    {
        input::registerKeyHandler(std::bind(&Camera::handleKeyPress, this,
            std::placeholders::_1, std::placeholders::_2
        ));
        input::registerCursorMovedHandler(std::bind(&Camera::handleCursorMove, this, 
            std::placeholders::_1, std::placeholders::_2
        ));
    }

    Camera::~Camera() {}

    void Camera::updatePos(float dt) {
        if (isMoveStateSet(FORWARD))
            m_pos += getFacingDir() * MOVE_SPEED * dt;
        if (isMoveStateSet(BACKWARD))
            m_pos -= getFacingDir() * MOVE_SPEED * dt;
        if (isMoveStateSet(RIGHT))
            m_pos += glm::cross(getFacingDir(), m_up) * MOVE_SPEED * dt;
        if (isMoveStateSet(LEFT))
            m_pos += glm::cross(m_up, getFacingDir()) * MOVE_SPEED * dt;
        if (isMoveStateSet(UP))
            m_pos += m_up * MOVE_SPEED * dt;
        if (isMoveStateSet(DOWN))
            m_pos -= m_up * MOVE_SPEED * dt;
    }

    void Camera::rotateMouse(float dx, float dy) {
        m_rotation.x -= dy;
        m_rotation.y -= dx;
    }

    const glm::vec3 &Camera::getPos() const {
        return m_pos;
    }

    glm::vec3 Camera::getFacingDir() const {
        // TODO: Use quaternions.
        // Currently, the camera behaves weirdly when looking down.
        // Gimbal lock is also occurring. 
        return glm::normalize(glm::vec3(
            glm::sin(glm::radians(m_rotation.y)) * glm::cos(glm::radians(m_rotation.x)),
            glm::sin(glm::radians(m_rotation.x)),
            glm::cos(glm::radians(m_rotation.y)) * glm::cos(glm::radians(m_rotation.x))
        ));
    }

    glm::mat4 Camera::getViewMatrix() const {
        return glm::lookAt(m_pos, m_pos + getFacingDir(), m_up);
    }

    void Camera::handleKeyPress(int key, int action) {
        // Masks are used to determine which direction the camera should be moving.
        // If we have the bit pattern 000000, then from left to right,
        // the moving state is: forward right backward left up down.

        // The corresponding values for each bit are from left to right:
        // 32, 16, 8, 4, 2, 1

        if (key == GLFW_KEY_W)
            setMoveState(FORWARD, action);
        if (key == GLFW_KEY_D)
            setMoveState(RIGHT, action);
        if (key == GLFW_KEY_S)
            setMoveState(BACKWARD, action);
        if (key == GLFW_KEY_A)
            setMoveState(LEFT, action);
        if (key == GLFW_KEY_LEFT_SHIFT)
            setMoveState(UP, action);
        if (key == GLFW_KEY_LEFT_CONTROL)
            setMoveState(DOWN, action);
    }

    void Camera::setMoveState(unsigned int bit, int action) {
        if (action == GLFW_PRESS) {
            // Turn the bit on
            m_moveState |= bit;
        } else if (action == GLFW_RELEASE) {
            // Turn the bit off
            m_moveState &= ~bit;
        }
    }

    bool Camera::isMoveStateSet(unsigned int bit) {
        return m_moveState & bit;
    }

    void Camera::handleCursorMove(float dx, float dy) {
        // TODO: Getting a little bit of choppiness when changing the camera direction
        // and position at the same time.
        rotateMouse(dx * 0.1f, dy * 0.1f);
    }
}