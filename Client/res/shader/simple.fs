#version 330 core

in vec3 Color;
in vec2 Texcoord;

out vec4 FragColor;

uniform sampler2D diffuse1;
uniform sampler2D diffuse2;

void main()
{
	vec3 tmp_color1 = texture(diffuse1, Texcoord).xyz;
	vec3 tmp_color2 = texture(diffuse2, Texcoord).xyz;

	FragColor = vec4(tmp_color1 * tmp_color2 * Color * 2.0, 1.0f);
}
