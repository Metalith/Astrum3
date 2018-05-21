#ifndef RENDER_SYS_HPP
#define RENDER_SYS_HPP

#include "system.hpp"
#include <GLFW\glfw3.h>
#include "components\transform.hpp"

class RenderSystem: public System {
	public:
		RenderSystem();
		void update();
		void addEntity(int e);

		void DrawGrid();
	private:
		GLFWwindow* window;
		Transform* tPlayer;
		
		std::vector<GLuint> vertexArrays;
		std::vector<int> sizes;
		std::vector<int> bSizes;
		std::vector<int> vSizes;

		int totalVerts = 0;
};

#endif
