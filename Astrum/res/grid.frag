#version 330 core

// Ouput data
out vec4 color;
in vec3 vertex;

void main()
{
	

	vec3 coord = vertex.xyz;

  // Compute anti-aliased world-space grid lines
  vec3 grid = abs(fract(coord - 0.5) - 0.5) / fwidth(coord);
  float line = min(min(grid.x, grid.y), grid.z);
	color = vec4(vec3(1.0 - min(line, 1.0)), 1.0);

}
