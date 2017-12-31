#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

#include <iostream>

#include "systems\render.hpp"
#include "common/shader.hpp"

#include "components/player.hpp"
#include "components/mesh.hpp"

#include "engine.hpp"

GLuint programID;
GLuint vertexbuffer;
GLuint normalbuffer;
GLuint elementbuffer;

GLuint ProjID;
GLuint ModelID;
GLuint ViewID;

glm::mat4 Projection;
glm::mat4 View;
glm::mat4 Model;
std::vector<unsigned short> indices;
RenderSystem::RenderSystem() {
	std::cerr << "New System :: Render!" << std::endl;
	setComponent<Player>();
	setComponent<Mesh>();
	this->window = glfwGetCurrentContext();

	// Dark blue background
	glClearColor(0.4f, 0.4f, 0.4f, 0.0f);


	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	//    glCullFace(GL_FRONT);
	  //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	programID = LoadShaders("../res/Voxel.vert", "../res/Voxel.frag");

	// Get a handle for our "MVP" uniform
	ProjID = glGetUniformLocation(programID, "projection");
	ViewID = glGetUniformLocation(programID, "view");
	ModelID = glGetUniformLocation(programID, "model");
	// Our ModelViewProjection : multiplication of our 3 matrices
}

void RenderSystem::update() {
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Use our shader
	glUseProgram(programID);



	glm::vec3 direction(0, 0, 1);
	glm::vec3 right(1, 0, 0);
	direction = direction * tPlayer->orientation;
	right = right * tPlayer->orientation;
	glm::vec3 up = glm::cross(direction, right);
	// Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 500.0f);
	// Camera matrix
	View = glm::lookAt(
		tPlayer->position,           // Camera is at player
		tPlayer->position + direction, // and looks here : at the same position, plus "direction"
		up // Head is up : cross of direction and right
	);
	// Model matrix : an identity matrix (model will be at the origin)
	Model = glm::mat4(1.0f);

	glUniformMatrix4fv(ProjID, 1, GL_FALSE, &Projection[0][0]);
	glUniformMatrix4fv(ViewID, 1, GL_FALSE, &View[0][0]);
	glUniformMatrix4fv(ModelID, 1, GL_FALSE, &Model[0][0]);

	for (int i = 0; i < vertexArrays.size(); i++) {
		glBindVertexArray(vertexArrays[i]); // Bind our Vertex Array Object
		glEnableVertexAttribArray(0);
		// glEnableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		// glDrawElements(GL_TRIANGLES, sizes[i], GL_UNSIGNED_INT, (void*)0);
		glDrawArrays(GL_TRIANGLES, 0, vSizes[i]);
		glBindVertexArray(0); // Unbind our Vertex Array Object
	}

	// Swap buffers
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void RenderSystem::addEntity(int e) {
	Transform* tmp = nullptr;
	if ((tmp = System::engine->getComponent<Transform>(e)) != nullptr) {
		tPlayer = tmp;
		return;
	}
	System::addEntity(e);
	Mesh* m = engine->getComponent<Mesh>(e);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, m->vertices.size() * sizeof(GLfloat), &m->vertices[0], GL_STREAM_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// GLuint normalbuffer;
	// glGenBuffers(1, &normalbuffer);
	// glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	// glBufferData(GL_ARRAY_BUFFER, m->normals.size() * sizeof(GLfloat), &m->normals[0], GL_STATIC_DRAW);
	// glEnableVertexAttribArray(1);
	// glVertexAttribPointer(
	// 		1,                  // attribute. No particular reason for 0, but must match the layout in the shader.
	// 		3,                  // size
	// 		GL_FLOAT,           // type
	// 		GL_FALSE,           // normalized?
	// 		0,                  // stride
	// 		(void*)0            // array buffer offset
	// 		);

	/*GLuint indexbuffer;
	glGenBuffers(1, &indexbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m->indices.size() * sizeof(int), &m->indices[0], GL_STATIC_DRAW);*/

	vertexArrays.push_back(VertexArrayID);
	sizes.push_back(m->indices.size());
	bSizes.push_back(m->bounds.size() / 3);
	vSizes.push_back(m->vertices.size() / 3);
	totalVerts += m->vertices.size() / 3;

	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}