#version 330 core

layout (location = 0) in vec3 Pos;
layout (location = 1) in vec2 UV;

out vec2 Texcoord;

void main()
{
	Texcoord = UV;
	gl_Position = vec4(Pos.xyz, 1.0);
}
