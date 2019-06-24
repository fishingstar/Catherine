#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;

out vec2 Texcoord;
out vec3 WorldNormal;
out vec3 WorldPos;

uniform mat4 view;
uniform mat4 projection;

void main()
{
   gl_Position = projection * view * vec4(aPos.xyz, 1.0);
   Texcoord = aUV;
   WorldNormal = aNormal.xyz;
   WorldPos = aPos.xyz;
}
