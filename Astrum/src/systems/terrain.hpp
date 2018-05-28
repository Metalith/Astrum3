#ifndef TERRAIN_SYS_HPP
#define TERRAIN_SYS_HPP

#include "system.hpp"
#include "components\renderable.hpp"
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
using namespace glm;

class TerrainSystem: public System {
	public:
		TerrainSystem();
		void update();

	private:
		void GenerateCube(int x, int y, int z, Renderable* r);
		float sdf(glm::vec3 pos);
		glm::vec3 interp(glm::vec3 vert1, glm::vec3 vert2);

		void GenerateAsteroid(int x, int y, int z, Renderable* r); // Replace with flyweight/Command
};

#endif