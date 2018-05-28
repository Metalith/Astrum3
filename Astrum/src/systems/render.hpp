#ifndef RENDER_SYS_HPP
#define RENDER_SYS_HPP

#include "system.hpp"
#include <GLFW\glfw3.h>
#include "components\transform.hpp"
#include "gui\imgui.h"

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
		std::vector<int> vSizes;

		void RenderGUI();

		//IMGUI Functions and variables
		void ImGui_RenderDrawData(ImDrawData* draw_data);
		bool ImGui_CreateDeviceObjects();
		void ImGui_InvalidateDeviceObjects();
		bool ImGui_CreateFontsTexture();


		char         g_GlslVersion[32] = "#version 330";
		int          g_ShaderHandle = 0, g_VertHandle = 0, g_FragHandle = 0;
		int          g_AttribLocationTex = 0, g_AttribLocationProjMtx = 0;
		int          g_AttribLocationPosition = 0, g_AttribLocationUV = 0, g_AttribLocationColor = 0;
		unsigned int g_VboHandle = 0, g_ElementsHandle = 0;
		GLuint       g_FontTexture = 0;

};

#endif
