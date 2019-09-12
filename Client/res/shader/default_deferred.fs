#version 330 core

in vec3 WorldPos;
in vec3 WorldNormal;

layout (location = 0) out vec4 GColor;
layout (location = 1) out vec4 GNormal;
layout (location = 2) out vec4 GMask;

uniform vec3 viewPos;

void main()
{
	vec3 tmp_normal = normalize(WorldNormal);
	vec3 tmp_viewDir = normalize(viewPos.xyz - WorldPos);

	vec3 tmp_diffuse = vec3(1.0, 1.0, 1.0);

	GColor = vec4(tmp_diffuse, 1.0f);
	GNormal = vec4(tmp_normal, 1.0f);
	GMask = vec4(0.0f, 0.0f, 0.0f, 0.0f);
}
