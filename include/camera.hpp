#pragma once

#include <glm/glm.hpp>

#define MOVE_SPEED 5.0f
#define ROTATE_SPEED 90.0f

typedef enum dir {
    FORWARD, BACK, LEFT, RIGHT, UP, DOWN,
} dir_t;

class camera
{
private:
    glm::vec3 pos;
    glm::vec3 rotation;
    glm::vec3 up;
public:
    camera(glm::vec3 pos, glm::vec3 rotation, glm::vec3 up);
    ~camera();

    void move(dir_t dir, float dt);
    void rotateKey(dir_t dir, float dt);
    void rotateMouse(float dx, float dy);

    glm::vec3 getFacingDir();
    glm::mat4 getViewMatrix();
};
