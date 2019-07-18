#version 330 core

layout (location = 0) in vec3 Pos;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec3 Tangent;
layout (location = 3) in vec2 UV;

out vec2 Texcoord;
out vec3 WorldNormal;
out vec3 WorldTangent;
out vec3 WorldPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	Texcoord = UV;
	WorldNormal = vec4(model * vec4(Normal.xyz, 0.0)).xyz;
	WorldTangent = vec4(model * vec4(Tangent.xyz, 0.0)).xyz;
	WorldPos = vec4(model * vec4(Pos.xyz, 1.0)).xyz;
	gl_Position = projection * view * model * vec4(Pos.xyz, 1.0);
}
