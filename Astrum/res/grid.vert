#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 vertex;

void main(){
	vertex = position * 100;

    gl_Position = (projection * view * model) * vec4(position * 100, 1.0f);

}

