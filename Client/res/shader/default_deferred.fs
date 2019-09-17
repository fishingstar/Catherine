#version 330 core

in vec3 WorldPos;
in vec3 WorldNormal;

layout (location = 0) out vec4 GColor;
layout (location = 1) out vec4 GNormal;
layout (location = 2) out vec4 GMask;

uniform vec3 viewPos;
uniform mat4 lightview;
uniform mat4 lightprojection;

uniform sampler2D shadowmap;

void main()
{
	vec3 tmp_normal = normalize(WorldNormal);
	vec3 tmp_viewDir = normalize(viewPos.xyz - WorldPos);

	vec3 tmp_diffuse = vec3(1.0, 1.0, 1.0);

	// shadow
	vec4 tmp_lightClipPos = lightprojection * lightview * vec4(WorldPos, 1.0);
	vec4 tmp_lightScreenPos = (tmp_lightClipPos.xyzw / tmp_lightClipPos.w + 1.0) / 2.0;
	float tmp_depth = texture(shadowmap, tmp_lightScreenPos.xy).x + 0.01;
	float tmp_shadow = step(tmp_lightScreenPos.z, tmp_depth);

	GColor = vec4(tmp_diffuse, tmp_shadow);
	GNormal = vec4(tmp_normal, 1.0f);
	GMask = vec4(0.0f, 0.0f, 0.0f, 0.0f);
}
