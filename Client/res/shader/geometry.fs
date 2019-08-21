#version 330 core

in vec2 Texcoord;
in vec3 WorldNormal;
in vec3 WorldTangent;
in vec3 WorldBinormal;
in vec3 WorldPos;

out vec4 out_Position;
out vec4 out_Albedo;
out vec4 out_Normal;

uniform sampler2D diffuse;
uniform sampler2D normalmap;

void main()
{
	vec3 tmp_normal = normalize(WorldNormal);
	vec3 tmp_tangent = normalize(WorldTangent);
	vec3 tmp_binormal = normalize(WorldBinormal);

	vec3 tmp_diffuse = texture(diffuse, Texcoord).xyz;
	vec3 tmp_normalMap = texture(normalmap, Texcoord).xyz;
	tmp_normalMap = normalize(tmp_normalMap * 2.0 - 1.0);
	tmp_normalMap = normalize(mat3(tmp_tangent, tmp_binormal, tmp_normal) * tmp_normalMap);
	// nanosuit's normal is wrong, turn off
	tmp_normalMap = tmp_normal;

	out_Position.xyz = WorldPos.xyz;
	out_Albedo.rgb = tmp_diffuse.rgb;
	out_Normal.xyz = tmp_normal.xyz;
}
