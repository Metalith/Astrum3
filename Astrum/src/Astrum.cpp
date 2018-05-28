// Astrum.cpp : Defines the entry point for the console application.
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
// Include standard headers
#include <string>
#include <fstream>
#include <ctime>

#include "common\debugOutput.hpp"

#include "gui/imgui.h"

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

#include "engine.hpp"
#include "systems/render.hpp"
#include "systems/controls.hpp"	
#include "systems/terrain.hpp"

#include "components/player.hpp"
#include "components/transform.hpp"

#include "common/quaternion_utils.hpp"

bool		CreateGameWindow(GLFWwindow* window);
std::string	UpdateVersion();

static void glfw_error_callback(int error, const char* description)
{
	std::cerr << "Error " << error << ", " <<  description;
}

int main() {
	try
	{
		static OutputDebugStringBuf<char> charDebugOutput;
		std::cout.rdbuf(&charDebugOutput);
		std::cerr.rdbuf(&charDebugOutput);
		std::clog.rdbuf(&charDebugOutput);

		static OutputDebugStringBuf<wchar_t> wcharDebugOutput;
		std::wcout.rdbuf(&wcharDebugOutput);
		std::wcerr.rdbuf(&wcharDebugOutput);
		std::wclog.rdbuf(&wcharDebugOutput);

		glfwSetErrorCallback(glfw_error_callback);
		if (!CreateGameWindow(window)) return -1;
		srand(time(NULL));
		//setSDF();
		Engine e = Engine(); // Make static
		// EntityFactory::CreatePlayer(x, y, z)
		int player = e.createEntity();
		e.addComponent(player, new Player());
		Transform tmp = Transform();
		tmp.position = vec3(10, 10, -10);
		vec3 desiredDir = -tmp.position;
		vec3 desiredUp = vec3(0.0f, 1.0f, 0.0f); // +Y
		mat4 View = glm::lookAt(
			-tmp.position, // Camera is at (4,3,-3), in World Space
			glm::vec3(0, 0, 0), // and looks at the origin
			glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);
		tmp.orientation = toQuat(View);

		e.addComponent(player, &tmp);
		e.addSystem(new TerrainSystem());
		e.addSystem(new ControlSystem()); // Jitters because we dont have delta time based movement, will run with variable time lengths resulting in random fast movement
		e.addSystem(new RenderSystem());
		window = glfwGetCurrentContext();
		glfwSwapInterval(1);

		while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
			glfwWindowShouldClose(window) == 0) e.update();

		//ImGui_ImplGlfwGL3_Shutdown();
		ImGui::DestroyContext();

		// Close OpenGL window and terminate GLFW
		glfwDestroyWindow(window);
		glfwTerminate();
	}
	catch (std::exception& e)
	{

	}
	return 0;
}

bool CreateGameWindow(GLFWwindow* window) {
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return false;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(1024, 768, ("Engine Ver 0.0." + UpdateVersion()).c_str(), NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwSwapInterval(1);

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	// Hide the mouse and enable unlimited mouvement
	// glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set the mouse at the vertex of the screen
	glfwPollEvents();
	glfwSetCursorPos(window, 1024 / 2, 768 / 2);

	return true;
}


std::string UpdateVersion() {
	return "0.0.No";
}
