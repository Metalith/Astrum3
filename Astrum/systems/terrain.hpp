#ifndef TERRAIN_SYS_HPP
#define TERRAIN_SYS_HPP

#include "system.hpp"
#include "components\mesh.hpp"
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
using namespace glm;

class TerrainSystem: public System {
	public:
		TerrainSystem();
		void update();

	private:
		void GenerateCube(int x, int y, int z, Mesh * mesh);
		float sdf(glm::vec3 pos);
		glm::vec3 interp(glm::vec3 vert1, glm::vec3 vert2);
};

#endif