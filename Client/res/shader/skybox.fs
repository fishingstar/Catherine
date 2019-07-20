#version 330 core

in vec3 TexCoords;

out vec4 FragColor;

uniform samplerCube environment;

void main()
{    
    FragColor = texture(environment, TexCoords);
}