#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace gl::engine {
    const float MOVE_SPEED = 5.0f;
    const float ROTATE_SPEED = 90.0f;

    class Camera {
    public:
        Camera(const glm::vec3 &pos, const glm::vec3 &rotation);
        ~Camera();

        void updatePos(float dt);
        void rotateMouse(float dx, float dy);

        const glm::vec3 &getPos() const;
        glm::quat getOrientation() const;
        glm::vec3 getForward() const;
        glm::vec3 getUp() const;
        glm::mat4 getViewMatrix() const;
    private:
        glm::vec3 m_pos;
        glm::vec3 m_rotation;

        unsigned int m_moveState;

        void handleKeyPress(int key, int action);
        void handleCursorMove(float dx, float dy);

        void setMoveState(unsigned int bit, int action);
        bool isMoveStateSet(unsigned int bit);
    };
}