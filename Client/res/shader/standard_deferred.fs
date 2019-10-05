#version 330 core

in vec2 Texcoord;
in vec3 WorldNormal;
in vec3 WorldTangent;
in vec3 WorldBinormal;
in vec3 WorldPos;

layout (location = 0) out vec4 GColor;
layout (location = 1) out vec4 GNormal;
layout (location = 2) out vec4 GMask;

uniform float ambient;
uniform mat4 lightview;
uniform mat4 lightprojection;

uniform sampler2D albedo;
uniform sampler2D normalmap;
uniform sampler2D metallicmap;
uniform sampler2D roughnessmap;
uniform sampler2D shadowmap;

void main()
{
	vec3 tmp_normal = normalize(WorldNormal);
	vec3 tmp_tangent = normalize(WorldTangent);
	vec3 tmp_binormal = normalize(WorldBinormal);

	vec3 tmp_albedo = texture(albedo, Texcoord).xyz;
	vec3 tmp_normaldir = texture(normalmap, Texcoord).xyz;
	tmp_normaldir = normalize(tmp_normaldir * 2.0 - 1.0);
	tmp_normaldir = normalize(mat3(tmp_tangent, tmp_binormal, tmp_normal) * tmp_normaldir);
	float tmp_metallic = texture(metallicmap, Texcoord).r;
	float tmp_roughness = texture(roughnessmap, Texcoord).r;

	// shadow
	vec4 tmp_lightClipPos = lightprojection * lightview * vec4(WorldPos, 1.0);
	vec4 tmp_lightScreenPos = (tmp_lightClipPos.xyzw / tmp_lightClipPos.w + 1.0) / 2.0;
	float tmp_depth = texture(shadowmap, tmp_lightScreenPos.xy).x + 0.01;
	float tmp_shadow = 1.0 - step(tmp_lightScreenPos.z, 1.0) * step(tmp_depth, tmp_lightScreenPos.z);

	GColor = vec4(tmp_albedo, tmp_shadow);
	GNormal = vec4(tmp_normaldir, 1.0);
	GMask = vec4(tmp_metallic, tmp_roughness, 1.0, 1.0);
}
