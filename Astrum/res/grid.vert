#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 vertex;

void main(){
	vertex = position;

	gl_Position = (projection * view * model) * vec4(position, 1.0f);

}

