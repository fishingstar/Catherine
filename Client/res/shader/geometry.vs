#version 330 core

layout (location = 0) in vec3 Pos;
layout (location = 1) in vec2 UV;

out vec2 Texcoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	Texcoord = UV;
	gl_Position = vec4(Pos.xyz, 1.0);
}
