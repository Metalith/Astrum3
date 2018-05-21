#ifndef COMPONENT_MESH
#define COMPONENT_MESH

#include "components\component.hpp"

#include <vector>
#include <GLFW\glfw3.h>

class Mesh : public Component {
	public:
		int getID() { return 0; }
		std::vector<GLfloat> vertices;
		std::vector<GLfloat> bounds;
		std::vector<GLfloat> normals;
		std::vector<int> indices;
};

#endif
