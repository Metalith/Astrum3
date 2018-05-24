#include "controls.hpp"
#include "system.hpp"
#include "render.hpp"
#include "engine.hpp"
#include "components/player.hpp"
#include "components/transform.hpp"

#include <iostream>

#include "gui\imgui.h"

bool ControlSystem::moveW;
bool ControlSystem::moveA;
bool ControlSystem::moveS;
bool ControlSystem::moveD;
bool ControlSystem::moveQ;
bool ControlSystem::moveE;

bool ControlSystem::dragScreen;
double ControlSystem::mStartX;
double ControlSystem::mStartY;

float ControlSystem::speed = 3.f;
float ControlSystem::rotSpeed = 3.f; // 3 units / seconds
float ControlSystem::mouseSpeed = 0.0025f;

ControlSystem::ControlSystem() {
	std::cout << "New System :: Control!" << std::endl;

	setComponent<Player>();
	this->window = glfwGetCurrentContext();

	glfwSetMouseButtonCallback(window, ControlSystem::mouse_callback);
	glfwSetKeyCallback(window, ControlSystem::key_callback);
}

void ControlSystem::addEntity(int e) {
	System::addEntity(e);
	tPlayer = System::engine->getComponent<Transform>(entities[0]);
}

void ControlSystem::update() {
	if (entities.size() != 1) {
		std::cout << "No Player for Control System" << std::endl;
		exit(EXIT_FAILURE);
	}
	static double lastTime = glfwGetTime();

	//TODO: Move Delta time to argument for systems
	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	ImGuiIO& io = ImGui::GetIO();

	double mouse_x, mouse_y;
	glfwGetCursorPos(this->window, &mouse_x, &mouse_y);

	if (glfwGetWindowAttrib(this->window, GLFW_FOCUSED))
	{
		// Set OS mouse position if requested (only used when ImGuiConfigFlags_NavEnableSetMousePos is enabled by user)
		if (io.WantSetMousePos)
		{
			glfwSetCursorPos(this->window, (double)io.MousePos.x, (double)io.MousePos.y);
		}
		else
		{
			io.MousePos = ImVec2((float)mouse_x, (float)mouse_y);
		}
	}
	else
	{
		io.MousePos = ImVec2(-FLT_MAX, -FLT_MAX);
	}

	if (dragScreen)
	{
		// Reset mouse position for next frame
		glfwSetCursorPos(window, mStartX, mStartY);
		OffsetOrientation(tPlayer->orientation, glm::vec3(0.0f, 1.0f, 0.0f), -mouseSpeed * (mStartX - mouse_x));
		OffsetOrientation(tPlayer->orientation, glm::vec3(1.0f, 0.0f, 0.0f), mouseSpeed * (mStartY - mouse_y));
	}
	glm::vec3 direction(0, 0, 1);
	glm::vec3 right(1, 0, 0);

	direction = direction * tPlayer->orientation;
	right = right * tPlayer->orientation;

	if (moveW) tPlayer->position += direction * deltaTime * speed;
	if (moveS) tPlayer->position -= direction * deltaTime * speed;
	if (moveA) tPlayer->position += right * deltaTime * speed;
	if (moveD) tPlayer->position -= right * deltaTime * speed;
	if (moveQ) OffsetOrientation(tPlayer->orientation, glm::vec3(0.0f, 0.0f, 1.0f), rotSpeed * deltaTime);
	if (moveE) OffsetOrientation(tPlayer->orientation, glm::vec3(0.0f, 0.0f, 1.0f), -rotSpeed * deltaTime);
	lastTime = currentTime;
}

void ControlSystem::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	bool set = (action != GLFW_RELEASE );
	switch (key){
		case GLFW_KEY_W: moveW = set; break;
		case GLFW_KEY_A: moveA = set; break;
		case GLFW_KEY_S: moveS = set; break;
		case GLFW_KEY_D: moveD = set; break;
		case GLFW_KEY_Q: moveQ = set; break;
		case GLFW_KEY_E: moveE = set; break;
		case GLFW_KEY_RIGHT_SHIFT:
		case GLFW_KEY_LEFT_SHIFT:
						if (set) ControlSystem::speed = 150.0f;
						else ControlSystem::speed = 3.0f;
						break;
	}
}

void ControlSystem::mouse_callback(GLFWwindow* window, int button, int action, int mods) {
	bool set = (action != GLFW_RELEASE);
	switch (button) {
		case GLFW_MOUSE_BUTTON_MIDDLE: 
			dragScreen = set;
			if (set)
				glfwGetCursorPos(window, &mStartX, &mStartY);
			break;
	}
}

void ControlSystem::OffsetOrientation(quat& q, const glm::vec3 &_axis, float fAngRad) {
	vec3 axis = normalize(_axis);
	axis = axis * sinf(fAngRad / 2.0f);
	float scalar = cosf(fAngRad / 2.0f);

	quat offset(scalar, axis.x, axis.y, axis.z);

	q = offset * q; //Transforms it via worldspace. Reference TUT 08 of arc synthesis
	q = normalize(q);
}
