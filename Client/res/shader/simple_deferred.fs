#version 330 core

in vec2 Texcoord;
in vec3 WorldNormal;
in vec3 WorldTangent;
in vec3 WorldBinormal;
in vec3 WorldPos;

layout (location = 0) out vec4 GColor;
layout (location = 1) out vec4 GNormal;
layout (location = 2) out vec4 GMask;

uniform vec3 viewPos;

uniform sampler2D diffuse;
uniform sampler2D normalmap;
uniform sampler2D specularmap;

void main()
{
	vec3 tmp_normal = normalize(WorldNormal);
	vec3 tmp_tangent = normalize(WorldTangent);
	vec3 tmp_binormal = normalize(WorldBinormal);
	vec3 tmp_viewDir = normalize(viewPos.xyz - WorldPos);

	vec3 tmp_diffuse = texture(diffuse, Texcoord).xyz;
	vec3 tmp_normalMap = texture(normalmap, Texcoord).xyz;
	tmp_normalMap = normalize(tmp_normalMap * 2.0 - 1.0);
	tmp_normalMap = normalize(mat3(tmp_tangent, tmp_binormal, tmp_normal) * tmp_normalMap);
	// nanosuit's normal is wrong, turn off
	tmp_normalMap = tmp_normal;
	vec4 tmp_specularmap = texture(specularmap, Texcoord).xyzw;

	GColor = vec4(tmp_diffuse, 1.0f);
	GNormal = vec4(tmp_normalMap, 1.0f);
	GMask = vec4(tmp_specularmap);
}
