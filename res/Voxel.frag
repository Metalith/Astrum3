#version 330 core
out vec4 color;

in vec3 vertexNormal;
in vec3 FragPos;

void main()
{
	vec3 objectColor = vec3(0.6, 0.6, 1.0) + (0.1 * abs(vertexNormal));
	vec3 lightPos = vec3(4, 3, -3);
	vec3 lightColor = vec3(1, 1, 1);

	// ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    vec3 X = dFdx(FragPos);
    vec3 Y = dFdy(FragPos);
    vec3 norm = -normalize(cross(X,Y));
    //vec3 norm = normalize(vertexNormal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
            
    vec3 result = (ambient + diffuse) * objectColor;
    color = vec4(result, 1.0);
}
