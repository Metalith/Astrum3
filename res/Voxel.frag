#version 330 core
out vec4 color;

in vec3 vertexNormal;
in vec3 FragPos;

void main()
{
	vec3 objectColor = vec3(0.6, 0.6, 1.0);
	vec3 lightPos = vec3(10, 15, -15);
	vec3 lightColor = vec3(1, 1, 1);

	// ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(vertexNormal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
	// specular
    //float specularStrength = 0.5;
    //vec3 viewDir = normalize(viewPos - FragPos);
    //vec3 reflectDir = reflect(-lightDir, norm);  
    //float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    //vec3 specular = specularStrength * spec * lightColor;   

    vec3 result = (ambient + diffuse) * objectColor;
    color = vec4(result, 1.0);
}
