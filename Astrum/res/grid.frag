#version 330 core

// Ouput data
out vec4 color;
in vec3 vertex;

void main()
{

	// Output color = red
	vec2 coord = vertex.xz;

	// Compute anti-aliased world-space grid lines
	vec2 grid = abs(fract(coord - 0.5) - 0.5) / fwidth(coord);
	float line = min(grid.x, grid.y);
	float a = 1.0;
	if (line > 0.5)
		a = 0.0;
	color = vec4(vec3(1.0 - min(line, 1.0)), a);
	if (line < 0.5 && abs(coord.x) < 0.02)
		color.rg = vec2(0);	
	if (line < 0.5 && abs(coord.y) < 0.02)
		color.rb = vec2(0);

}
