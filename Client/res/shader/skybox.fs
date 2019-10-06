#version 330 core

in vec3 TexCoords;

out vec4 FragColor;

uniform samplerCube environment;

void main()
{
	vec3 tmp_color = pow(texture(environment, TexCoords).rgb, vec3(2.2));
    FragColor = vec4(tmp_color, 1.0);
}