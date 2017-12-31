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
		bool sdf(glm::vec3 pos);
};

#endif