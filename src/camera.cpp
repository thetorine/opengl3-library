#include <glm/gtc/matrix_transform.hpp>

#include "camera.hpp"

camera::camera(glm::vec3 pos, glm::vec3 rotation, glm::vec3 up)
: pos(pos), rotation(rotation), up(up) {}

camera::~camera() {}

void camera::move(dir_t dir, float dt) {
    if (dir == FORWARD)
        pos += getFacingDir() * MOVE_SPEED * dt;
    if (dir == BACK)
        pos -= getFacingDir() * MOVE_SPEED * dt;
    if (dir == LEFT)
        pos += glm::cross(up, getFacingDir()) * MOVE_SPEED * dt;
    if (dir == RIGHT)
        pos += glm::cross(getFacingDir(), up) * MOVE_SPEED * dt;
    if (dir == UP)
        pos += up * MOVE_SPEED * dt;
    if (dir == DOWN)
        pos -= up * MOVE_SPEED * dt;
}

void camera::rotateKey(dir_t dir, float dt) {
    if (dir == LEFT)
        rotation.y += ROTATE_SPEED * dt;
    if (dir == RIGHT)
        rotation.y += -ROTATE_SPEED * dt;
}

void camera::rotateMouse(float dx, float dy) {
    rotation.x -= dy;
    rotation.y -= dx;
}

glm::vec3 camera::getFacingDir() {
    return glm::normalize(glm::vec3(
        glm::sin(glm::radians(rotation.y)) * glm::cos(glm::radians(rotation.x)),
        glm::sin(glm::radians(rotation.x)),
        glm::cos(glm::radians(rotation.y)) * glm::cos(glm::radians(rotation.x))
    ));
}

glm::mat4 camera::getViewMatrix() {
    return glm::lookAt(pos, pos + getFacingDir(), up);
}
