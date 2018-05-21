#ifndef CONTROL_SYS_HPP
#define CONTROL_SYS_HPP

#include "system.hpp"
#include "components\transform.hpp"

#include <GLFW\glfw3.h>

class ControlSystem: public System {
	public:
		ControlSystem();
		void update();
		void addEntity(int e);

		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);	  // Need to not make these static
		static void mouse_callback(GLFWwindow* window, int button, int action, int mods);
	private:
		GLFWwindow* window;
		Transform* tPlayer = nullptr;

		static float speed;
		static float rotSpeed;
		static float mouseSpeed;

		static bool dragScreen;
		static double mStartX, mStartY;

		static bool  moveW, moveS, moveD, moveA, moveQ, moveE;

		void OffsetOrientation(quat& q, const glm::vec3 &_axis, float fAngRad);
};
#endif
