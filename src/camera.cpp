#include <glm/gtc/matrix_transform.hpp>

#include "camera.hpp"

namespace engine {

    Camera::Camera(glm::vec3 pos, glm::vec3 rotation, glm::vec3 up)
        : m_pos(pos), m_rotation(rotation), m_up(up) {}

    Camera::~Camera() {}

    void Camera::move(dir_t dir, float dt) {
        if (dir == FORWARD)
            m_pos += getFacingDir() * MOVE_SPEED * dt;
        if (dir == BACK)
            m_pos -= getFacingDir() * MOVE_SPEED * dt;
        if (dir == LEFT)
            m_pos += glm::cross(m_up, getFacingDir()) * MOVE_SPEED * dt;
        if (dir == RIGHT)
            m_pos += glm::cross(getFacingDir(), m_up) * MOVE_SPEED * dt;
        if (dir == UP)
            m_pos += m_up * MOVE_SPEED * dt;
        if (dir == DOWN)
            m_pos -= m_up * MOVE_SPEED * dt;
    }

    void Camera::rotateKey(dir_t dir, float dt) {
        if (dir == LEFT)
            m_rotation.y += ROTATE_SPEED * dt;
        if (dir == RIGHT)
            m_rotation.y += -ROTATE_SPEED * dt;
    }

    void Camera::rotateMouse(float dx, float dy) {
        m_rotation.x -= dy;
        m_rotation.y -= dx;
    }

    glm::vec3 Camera::getPos() {
        return m_pos;
    }

    glm::vec3 Camera::getFacingDir() {
        return glm::normalize(glm::vec3(
            glm::sin(glm::radians(m_rotation.y)) * glm::cos(glm::radians(m_rotation.x)),
            glm::sin(glm::radians(m_rotation.x)),
            glm::cos(glm::radians(m_rotation.y)) * glm::cos(glm::radians(m_rotation.x))
        ));
    }

    glm::mat4 Camera::getViewMatrix() {
        return glm::lookAt(m_pos, m_pos + getFacingDir(), m_up);
    }

}