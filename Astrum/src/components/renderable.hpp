#ifndef COMPONENT_RENDERABLE
#define COMPONENT_RENDERABLE

#include "components\component.hpp"

#include <vector>
#include <GLFW\glfw3.h>

class Renderable : public Component {
public:
	std::vector<GLfloat> vertices;
	std::vector<GLfloat> bounds;
	std::vector<GLfloat> normals;
	std::vector<int> indices;

	unsigned char shaderID;
	bool doubleSided;
};

#endif