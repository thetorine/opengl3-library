#pragma once

#include <glm/glm.hpp>

#define MOVE_SPEED 5.0f
#define ROTATE_SPEED 90.0f

namespace engine {
    class Camera {
    public:
        Camera(const glm::vec3 &pos, const glm::vec3 &rotation, const glm::vec3 &up);
        ~Camera();

        void updatePos(float dt);
        void rotateMouse(float dx, float dy);

        const glm::vec3 &getPos() const;
        glm::vec3 getFacingDir() const;
        glm::mat4 getViewMatrix() const;
    private:
        glm::vec3 m_pos;
        glm::vec3 m_rotation;
        glm::vec3 m_up;

        unsigned int m_moveState;

        void handleKeyPress(int key, int action);
        void handleCursorMove(float dx, float dy);

        void setMoveState(unsigned int bit, int action);
        bool isMoveStateSet(unsigned int bit);
    };
}