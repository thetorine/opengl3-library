#pragma once

#include <glm/glm.hpp>

#define MOVE_SPEED 5.0f
#define ROTATE_SPEED 90.0f

namespace engine {
	typedef enum dir {
		FORWARD, BACK, LEFT, RIGHT, UP, DOWN,
	} dir_t;

	class Camera {
	public:
		Camera(glm::vec3 pos, glm::vec3 rotation, glm::vec3 up);
		~Camera();

		void move(dir_t dir, float dt);
		void rotateKey(dir_t dir, float dt);
		void rotateMouse(float dx, float dy);

		glm::vec3 getPos();
		glm::vec3 getFacingDir();
		glm::mat4 getViewMatrix();
	private:
		glm::vec3 m_pos;
		glm::vec3 m_rotation;
		glm::vec3 m_up;
	};
}