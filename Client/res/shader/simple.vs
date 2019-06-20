#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aUV;

out vec3 Color;
out vec2 Texcoord;

uniform mat4 view;
uniform mat4 projection;

void main()
{
   gl_Position = projection * view * vec4(aPos.xyz, 1.0);
   Color = aColor;
   Texcoord = aUV;
}
